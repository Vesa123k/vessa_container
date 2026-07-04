How to use


	gx_vessa::CustomVector<int> cv;
	cv.multiple_push_back(1, 2, 3, 4, 5, 6);
	cv.multiple_push_back(123412);

	cv.for_each([](const int element, const int at) {
		std::cout << "Element " << at << std::endl;
		std::cout << element << std::endl;
	});


	gx_vessa::Unorder_map<int, std::string> gx_m;
	gx_m.insert(1, "Hello, world");
	gx_m.insert(2, "Want to");
	// Normal way
	gx_m.get_value(1) = "World";

	// Easier way
	gx_m[1] = "World are something";


	gx_m.for_each_values([](const std::string& value, const int at) {
		std::cout << "Part : " << at << " value : " << value << std::endl;
	});

	std::cout << "--------------- iota test ------------------" << std::endl;
	// Print index 0-9
	gx_vessa::iota::ranges(10, [&](const int index) {
		std::cout << index << std::endl;
	});
