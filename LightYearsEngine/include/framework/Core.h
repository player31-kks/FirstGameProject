#pragma once
#include <cstdio>
#include <memory>
#include <map>
#include <unordered_map>

namespace ly
{
	template<typename T>
	using unique = std::unique_ptr<T>;

	template<typename T>
	using shared = std::shared_ptr<T>;

	template<typename T>
	using weak = std::weak_ptr<T>;

	template<typename T>
	using List = std::vector<T>;

	template<typename K,typename V, typename Pr = std::less<K>>
	using Map = std::map<K, V, Pr>;

	template<typename K, typename V, typename Hasher = std::hash<K>>
	using Dictionary = std::unordered_map<K, V, Hasher>;
	// a macro
	#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}


