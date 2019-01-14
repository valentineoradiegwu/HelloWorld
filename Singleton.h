#pragma once
class Singleton
{
public:
	static const Singleton& GetSingleton()
	{
		static Singleton myinstance{};
		return myinstance;
	}
	Singleton(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(const Singleton&) = delete;
private:
	Singleton() = delete;
};
