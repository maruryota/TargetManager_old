#pragma once
#ifndef TARGETINFO_H
#define TARGETINFO_H
#include <iostream>
#include <sstream>
#include <vector>

class TargetInfo {
public:
	TargetInfo();
	std::vector< double > pose;
	std::string kind;
};

#endif // TARGETINFO_H