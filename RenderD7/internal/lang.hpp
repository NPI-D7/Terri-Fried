#pragma once
#include <string>
#include "json.hpp"

/// RenderD7::Lang
namespace RenderD7::Lang
{
    /// Get the 3ds System Language
    std::string getSys();
    /// Get a translated string
    /// key: The Key so the code can find your string
    std::string get(const std::string &key);
        /// Load the lang file from dir structure en/app.json for sample
        /// lang: the folder name en, fr, de ... . I prefer geSys()
	void load(const std::string &lang);
} /// RenderD7::Lang
