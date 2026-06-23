#pragma once

#include <string> 
#include <vector>
#include <nlohmann/json.hpp>
#include <filesystem>

class Loc 
{
private:
   Loc() = default;
   nlohmann::json data;

   static Loc& instance();
   static std::vector<std::string> split(const std::string& s, char delimiter);
public: 
   Loc(const Loc&) = delete;
   Loc& operator=(const Loc&) = delete;

   static bool load(const std::filesystem::path& filename);
   static std::string get(const std::string& path);
};