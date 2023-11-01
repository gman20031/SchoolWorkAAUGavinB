int* CreateIntArray(int total, ...) //takes any number of int inputs and makes an array out of them
{
	va_list allInts; //is this just an empty data type?

	if (total <= 0) // dont run function if I didnt get inputs
		return nullptr;

	int* outputArray = (int*)malloc(total * sizeof(int));
	if (outputArray == nullptr) // if malloc failed, quit function
		return nullptr;

	va_start(allInts, total); // little unsure on the usage of va_list in general
	//Somehow va_list interacts with the parameters of this function to give me a list of  all ints inputed

		for (int i = 0; i < total; i++)
			outputArray[i] = va_arg(allInts, int); //unsure how this does not just only give the first int inputed.

	va_end(allInts);

	return outputArray;
}//createInt Array function