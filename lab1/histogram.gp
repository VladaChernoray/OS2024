system("mkdir -p histogram")

set terminal pngcairo transparent enhanced font "arial,10" fontscale 2.0 size 2000, 1000
set output 'histogram/histogram_normal_distribution_integer.png'

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "white" behind

set title "Normal Distribution (integer)" font ",15"
set xlabel "Sizes"
set ylabel "Execution Time (seconds)"
set grid

set style fill solid 
set boxwidth 1 relative

plot 'data\integer\Data_Normal Distribution\Bubble Sort.txt' using 2:xtic(1) with histogram title 'Bubble Sort', \
     'data\integer\Data_Normal Distribution\Insertion Sort.txt' using 2:xtic(1) with histogram title 'Insertion Sort', \
     'data\integer\Data_Normal Distribution\Merge Sort.txt' using 2:xtic(1) with histogram title 'Merge Sort', \
     'data\integer\Data_Normal Distribution\Quick Sort.txt' using 2:xtic(1) with histogram title 'Quick Sort'

set terminal pngcairo transparent enhanced font "arial,10" fontscale 2.0 size 2000, 1000
set output 'histogram/histogram_uniform_distribution_integer.png'

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "white" behind

set title "Uniform Distribution (integer)" font ",15"
set xlabel "Sizes"
set ylabel "Execution Time (seconds)"
set grid

set style fill solid 
set boxwidth 1 relative


plot 'data\integer\Data_Uniform Distribution\Bubble Sort.txt' using 2:xtic(1) with histogram title 'Bubble Sort', \
     'data\integer\Data_Uniform Distribution\Insertion Sort.txt' using 2:xtic(1) with histogram title 'Insertion Sort', \
     'data\integer\Data_Uniform Distribution\Merge Sort.txt' using 2:xtic(1) with histogram title 'Merge Sort', \
     'data\integer\Data_Uniform Distribution\Quick Sort.txt' using 2:xtic(1) with histogram title 'Quick Sort'

set terminal pngcairo transparent enhanced font "arial,10" fontscale 2.0 size 2000, 1000
set output 'histogram/histogram_sorted_data_integer.png'

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "white" behind

set title "Sorted data (integer)" font ",15"
set xlabel "Sizes"
set ylabel "Execution Time (seconds)"
set grid

set style fill solid 
set boxwidth 1 relative


plot 'data\integer\Data_Sorted Data\Bubble Sort.txt' using 2:xtic(1) with histogram title 'Bubble Sort', \
     'data\integer\Data_Sorted Data\Insertion Sort.txt' using 2:xtic(1) with histogram title 'Insertion Sort', \
     'data\integer\Data_Sorted Data\Merge Sort.txt' using 2:xtic(1) with histogram title 'Merge Sort', \
     'data\integer\Data_Sorted Data\Quick Sort.txt' using 2:xtic(1) with histogram title 'Quick Sort'

set terminal pngcairo transparent enhanced font "arial,10" fontscale 2.0 size 2000, 1000
set output 'histogram/histogram_reverse_sorted_data_integer.png'

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "white" behind

set title "Reverse sorted data (integer)" font ",15"
set xlabel "Sizes"
set ylabel "Execution Time (seconds)"
set grid

set style fill solid 
set boxwidth 1 relative

plot 'data\integer\Data_Reverse Sorted Data\Bubble Sort.txt' using 2:xtic(1) with histogram title 'Bubble Sort', \
     'data\integer\Data_Reverse Sorted Data\Insertion Sort.txt' using 2:xtic(1) with histogram title 'Insertion Sort', \
     'data\integer\Data_Reverse Sorted Data\Merge Sort.txt' using 2:xtic(1) with histogram title 'Merge Sort', \
     'data\integer\Data_Reverse Sorted Data\Quick Sort.txt' using 2:xtic(1) with histogram title 'Quick Sort'



set terminal pngcairo transparent enhanced font "arial,10" fontscale 2.0 size 2000, 1000
set output 'histogram/histogram_normal_distribution_double.png'

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "white" behind

set title "Normal Distribution (double)" font ",15"
set xlabel "Sizes"
set ylabel "Execution Time (seconds)"
set grid

set style fill solid 
set boxwidth 1 relative

plot 'data\double\Data_Normal Distribution\Bubble Sort.txt' using 2:xtic(1) with histogram title 'Bubble Sort', \
     'data\double\Data_Normal Distribution\Insertion Sort.txt' using 2:xtic(1) with histogram title 'Insertion Sort', \
     'data\double\Data_Normal Distribution\Merge Sort.txt' using 2:xtic(1) with histogram title 'Merge Sort', \
     'data\doubler\Data_Normal Distribution\Quick Sort.txt' using 2:xtic(1) with histogram title 'Quick Sort'

set terminal pngcairo transparent enhanced font "arial,10" fontscale 2.0 size 2000, 1000
set output 'histogram/histogram_uniform_distribution_double.png'

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "white" behind

set title "Uniform Distribution (double)" font ",15"
set xlabel "Sizes"
set ylabel "Execution Time (seconds)"
set grid

set style fill solid 
set boxwidth 1 relative


plot 'data\double\Data_Uniform Distribution\Bubble Sort.txt' using 2:xtic(1) with histogram title 'Bubble Sort', \
     'data\double\Data_Uniform Distribution\Insertion Sort.txt' using 2:xtic(1) with histogram title 'Insertion Sort', \
     'data\double\Data_Uniform Distribution\Merge Sort.txt' using 2:xtic(1) with histogram title 'Merge Sort', \
     'data\double\Data_Uniform Distribution\Quick Sort.txt' using 2:xtic(1) with histogram title 'Quick Sort'

set terminal pngcairo transparent enhanced font "arial,10" fontscale 2.0 size 2000, 1000
set output 'histogram/histogram_sorted_data_double.png'

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "white" behind

set title "Sorted data (double)" font ",15"
set xlabel "Sizes"
set ylabel "Execution Time (seconds)"
set grid

set style fill solid 
set boxwidth 1 relative


plot 'data\double\Data_Sorted Data\Bubble Sort.txt' using 2:xtic(1) with histogram title 'Bubble Sort', \
     'data\double\Data_Sorted Data\Insertion Sort.txt' using 2:xtic(1) with histogram title 'Insertion Sort', \
     'data\double\Data_Sorted Data\Merge Sort.txt' using 2:xtic(1) with histogram title 'Merge Sort', \
     'data\double\Data_Sorted Data\Quick Sort.txt' using 2:xtic(1) with histogram title 'Quick Sort'

set terminal pngcairo transparent enhanced font "arial,10" fontscale 2.0 size 2000, 1000
set output 'histogram/histogram_reverse_sorted_data_double.png'

set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "white" behind

set title "Reverse sorted data (double)" font ",15"
set xlabel "Sizes"
set ylabel "Execution Time (seconds)"
set grid

set style fill solid 
set boxwidth 1 relative

plot 'data\double\Data_Reverse Sorted Data\Bubble Sort.txt' using 2:xtic(1) with histogram title 'Bubble Sort', \
     'data\double\Data_Reverse Sorted Data\Insertion Sort.txt' using 2:xtic(1) with histogram title 'Insertion Sort', \
     'data\double\Data_Reverse Sorted Data\Merge Sort.txt' using 2:xtic(1) with histogram title 'Merge Sort', \
     'data\double\Data_Reverse Sorted Data\Quick Sort.txt' using 2:xtic(1) with histogram title 'Quick Sort'
