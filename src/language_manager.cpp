#include "language_manager.hpp"

#include <fstream>
#include <sstream>

Loc &Loc::instance()
{
   static Loc instance;
   return instance;
}

std::vector<std::string> Loc::split(const std::string &s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);

   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   
   return tokens;
}

bool Loc::load(const std::filesystem::path& filename)
{
   std::ifstream file(filename);
   if (!file.is_open()) return false;
   try 
   {
      file >> instance().data;
      return true;
   } 
   catch (...) 
   {
      return false;
   }
}

std::string Loc::get(const std::string &path)
{
   try 
   {
      auto keys = split(path, '.');
      nlohmann::json current = instance().data;

      for (const auto& key : keys) 
      {
         if (!current.contains(key)) return path;
         current = current[key];
      }

      return current.is_string() ? current.get<std::string>() : path; 
   }
   catch (...)
   {
      return path;
   }
}
