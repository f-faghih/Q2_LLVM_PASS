#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"

using namespace llvm;

// Define the pass itself
struct MyPass : PassInfoMixin<MyPass> {
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
    // Initialize the histogram buckets
    int range1_10 = 0;
    int range10_100 = 0;
    int range100_1000 = 0;
    int range1000_inf = 0;

    // Iterate over every function in the module
    for (Function &F : M) {
      // Iterate over every basic block in the function
      for (BasicBlock &BB : F) {
        unsigned int instructionCount = 0;

        // Count the instructions in the basic block
        for (Instruction &I : BB) {
          ++instructionCount;
        }

        // Place the count in the appropriate histogram bucket
        if (instructionCount < 10) {
          range1_10++;
        } else if (instructionCount < 100) {
          range10_100++;
        } else if (instructionCount < 1000) {
          range100_1000++;
        } else {
          range1000_inf++;
        }
      }
    }

    // Output the results to a file
    std::error_code EC;
    raw_fd_ostream HistogramFile("histogram_data.txt", EC);
    if (!EC) {
      HistogramFile << "1-9 " << range1_10 << "\n";
      HistogramFile << "10-99 " << range10_100 << "\n";
      HistogramFile << "100-999 " << range100_1000 << "\n";
      HistogramFile << "1000-inf " << range1000_inf << "\n";
    } else {
      errs() << "Error opening file: " << EC.message() << "\n";
    }

    return PreservedAnalyses::all();
  }
};

// Integration with the new pass manager
llvm::PassPluginLibraryInfo getMyPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "MyPass", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, ModulePassManager &MPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "mypass") {
                    MPM.addPass(MyPass());
                    return true;
                  }
                  return false;
                });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getMyPassPluginInfo();
}