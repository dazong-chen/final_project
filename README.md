# final_project
 
Cannot rotate the board too slow otherwise aceleration won't be detected due to board sensitivity.

Debug mode will print debug message of the xyz axis value and how many times the interrupt has been triggered. release mode won't print debug message
#define DEBUG_MODE is set in my_debug.h
if DEBUG_MODE is defined, program will run in debug mode which will first print MMA initialization sucess info, then print accelerometer xyz value and times run into PTA IRQ_Handler, and blink LED
if not defined, it will only print MMA initialization sucess info, and blink LED
