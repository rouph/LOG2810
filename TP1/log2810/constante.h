#pragma once
const int invalidDistance = 999999999;
//	std::cout << "Enter the patient's health risk " << endl
//		<< " 1 : low risk " << endl
//		<< " 2 : medium risk " << endl
//		<< " 3 : high risk " << endl;

namespace healthRisk {
	const int lowRisk = 1;
	const int mediumRisk = 2;
	const int highRisk = 3;
}

namespace pourcentage {
	namespace NINH {
		const double lowRisk = 6;
		const double mediumRisk = 12;
		const double highRisk = 48;
	}
}
namespace pourcentage {
	namespace LIion {
		const double lowRisk = 5;
		const double mediumRisk = 10;
		const double highRisk = 30;
	}
}