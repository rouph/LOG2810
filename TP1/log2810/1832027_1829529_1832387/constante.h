#pragma once
const int invalidDistance = 999999999;

namespace healthRisk {
	const int lowRisk = 1;
	const int mediumRisk = 2;
	const int highRisk = 3;
}

namespace Percentage {
	namespace NIMH {
		const double lowRisk = 6;
		const double mediumRisk = 12;
		const double highRisk = 48;
	}
}
namespace Percentage {
	namespace LIion {
		const double lowRisk = 5;
		const double mediumRisk = 10;
		const double highRisk = 30;
	}
}

namespace menuOption {
	namespace {
		const char updateMap = 'a';
		const char shortestPath = 'b';
		const char subGraph = 'c';
		const char quit = 'd';
	}
}