Please use Visual Studio to solve this problem. Then copy and paste your answers here as needed.


This function has an error.
//////////////////////////////////////////////////////////////////////////
// Shifts the value of each element down by one, and inserts 0 at the end.
// EXAMPLE: {1, 2, 3} becomes {2, 3, 0}
//////////////////////////////////////////////////////////////////////////
void ShiftArrayElements(int array[], int size)
{
        int i = 0;
        while (i < size)
        {
            array[i] = array[i + 1];
            ++i;
        }
        array[i] = 0;
}
	

Please do the following:
* Find out what the error is. Explain what it is and how you found it. What else could you have done to find the error?

    The error should be that you are attempting to acess memory out of the bounds of the array.
indicated by "array[i + 1]" this will eventually hit the end of the array, attempt to access something
outside of the scope of the array and either error or return garbage.
    Then you increate i by 1, bringing I oustide of the scope of the array, and replace whatever is there
with a 0.

* Investigate what is causing the error. List all the things you can do to investigate here.

    Two methods are, writing to the console every step of the proram to find out whats happening.
You would then see that it sets the last slot fo be some random value, or breaks at the last step.

    Or set a breakpoint during the while loop to see what happens every loop of the function.

* Fix the error. Explain what the fix is and why it fixes the issue. If there are alternative solutions, list any you can think of as well.

    Either way its an off by one error. You would need to iterate to before size, not to size.
to keep the code as intact as possible, you could add a special case for when i = size-1(the end of the array)
or just rewrite the loop to not include the final element of the array (for int i =0 ; i < size-1; ++i).
You would either way still need to manually account for the last element being set to zero.


* If you fixed the error, paste the corrected code here:
void ShiftArrayElements(int array[], int size)
{
        int i = 0;
        while (i < size)
        {
            if (i = size - 1)
            {
                array[i] = 0;
                break;
            }
            array[i] = array[i + 1];
            ++i;
        }
}
	