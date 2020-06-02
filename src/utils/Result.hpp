#pragma once

#include <string>

class Result
{
public:
	enum class Status { SUCCESS, FAIL };

private:
	Result::Status status;
	std::string errorMsg;
public:

	Result(Result::Status status, std::string errorMsg);
	~Result();

	static Result Success();
	static Result Fail(std::string errorMsg);

	Result::Status GetStatus();
	std::string GetErrorMsg();
};