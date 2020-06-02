#include "Result.hpp"

Result::Result(Result::Status status, std::string errorMsg)
{
	this->status = status;
	this->errorMsg = errorMsg;
}

Result::~Result() { }

Result Result::Success()
{
	return Result(Result::Status::SUCCESS, "");
}

Result Result::Fail(std::string errorMsg)
{
	return Result(Result::Status::FAIL, errorMsg);
}

Result::Status Result::GetStatus()
{
	return this->status;
}

std::string Result::GetErrorMsg()
{
	return this->errorMsg;
}
