set terminal pngcairo
set output "histogram.png"

set title "Basic Block Instruction Count Histogram"
set xlabel "Instruction Count Ranges"
set ylabel "Number of Basic Blocks"
set style data histograms
set style fill solid 1.0
set boxwidth 0.9
set yrange [0:*]
set xtics rotate by -45
plot "histogram_data.txt" using 2:xtic(1) with boxes notitle