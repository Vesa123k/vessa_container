How to use

very simple

int main()
{
	gx_vessa::CustomVector<std::string> cv;
	
	cv.multiple_push_back("Hello, world");

	std::cout << cv[0] << std::endl;
	Render(cv);
	

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

	using iota = gx_vessa::iota;

	iota::ranges(10, [&](const int index) {
		std::cout << index << std::endl;
	});

	std::cout << "------------------- gxc counter -----------------" << std::endl;

	gx_vessa::gx_counter::Value_State vState{};
	gx_vessa::gx_counter gxc{ 4, std::move(vState) };
	ChiliTimer timer;

	std::jthread t{ [&] {
		timer.Mark();
		gxc.Waitil_Predicate([&](const auto& state, const auto& value_input) -> bool {
			if (state == gxc.FULL)
			{
				return true;
			}
			else
			{
				return false;
			}
		});
		const auto t = timer.Peek();
		std::cout << t << " Seconds" << std::flush;
	}};
	
	std::this_thread::sleep_for(std::chrono::seconds(100));
	gxc.inc(4);


	return 0;
}
