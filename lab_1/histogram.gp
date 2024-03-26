system("mkdir -p histogram")

set terminal pngcairo transparent enhanced font "arial,10" fontscale 1.0 size 1200, 800
set output 'histogram/histogram_normal_distribution.png'

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "white" behind

set title "Normal Distribution"
set xlabel "Sizes"
set ylabel "Execution Time (seconds)"
set grid

set style fill solid border -1
set boxwidth 0.9 relative
set xtics rotate by -45

plot 'data\Data_Normal Distribution\Bubble Sort.txt' using 2:xtic(1) with histogram title 'Bubble Sort', \
     'data\Data_Normal Distribution\Insertion Sort.txt' using 2:xtic(1) with histogram title 'Insertion Sort', \
     'data\Data_Normal Distribution\Merge Sort.txt' using 2:xtic(1) with histogram title 'Merge Sort', \
     'data\Data_Normal Distribution\Quick Sort.txt' using 2:xtic(1) with histogram title 'Quick Sort'

set terminal pngcairo transparent enhanced font "arial,10" fontscale 1.0 size 1200, 800
set output 'histogram/histogram_uniform_distribution.png'

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "white" behind

set title "Uniform Distribution"
set xlabel "Sizes"
set ylabel "Execution Time (seconds)"
set grid

set style fill solid border -1
set boxwidth 0.9 relative
set xtics rotate by -45

plot 'data\Data_Uniform Distribution\Bubble Sort.txt' using 2:xtic(1) with histogram title 'Bubble Sort', \
     'data\Data_Uniform Distribution\Insertion Sort.txt' using 2:xtic(1) with histogram title 'Insertion Sort', \
     'data\Data_Uniform Distribution\Merge Sort.txt' using 2:xtic(1) with histogram title 'Merge Sort', \
     'data\Data_Uniform Distribution\Quick Sort.txt' using 2:xtic(1) with histogram title 'Quick Sort'

set terminal pngcairo transparent enhanced font "arial,10" fontscale 1.0 size 1200, 800
set output 'histogram/histogram_sorted_data.png'

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "white" behind

set title "Sorted data"
set xlabel "Sizes"
set ylabel "Execution Time (seconds)"
set grid

set style fill solid border -1
set boxwidth 0.9 relative
set xtics rotate by -45

plot 'data\Data_Sorted Data\Bubble Sort.txt' using 2:xtic(1) with histogram title 'Bubble Sort', \
     'data\Data_Sorted Data\Insertion Sort.txt' using 2:xtic(1) with histogram title 'Insertion Sort', \
     'data\Data_Sorted Data\Merge Sort.txt' using 2:xtic(1) with histogram title 'Merge Sort', \
     'data\Data_Sorted Data\Quick Sort.txt' using 2:xtic(1) with histogram title 'Quick Sort'

set terminal pngcairo transparent enhanced font "arial,10" fontscale 1.0 size 1200, 800
set output 'histogram/histogram_reverse_sorted_data.png'

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "white" behind

set title "Reverse sorted data"
set xlabel "Sizes"
set ylabel "Execution Time (seconds)"
set grid

set style fill solid border -1
set boxwidth 0.9 relative
set xtics rotate by -45

plot 'data\Data_Reverse Sorted Data\Bubble Sort.txt' using 2:xtic(1) with histogram title 'Bubble Sort', \
     'data\Data_Reverse Sorted Data\Insertion Sort.txt' using 2:xtic(1) with histogram title 'Insertion Sort', \
     'data\Data_Reverse Sorted Data\Merge Sort.txt' using 2:xtic(1) with histogram title 'Merge Sort', \
     'data\Data_Reverse Sorted Data\Quick Sort.txt' using 2:xtic(1) with histogram title 'Quick Sort'
