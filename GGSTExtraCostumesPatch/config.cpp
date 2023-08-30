#include "pch.h"
#include "config.h"

#include <iostream>
#include <filesystem>
//namespace fs = std::filesystem;
std::wstring PathAndName;
std::wstring OnlyPath;

bool config::enableConsole;
bool config::enableFileAccessLog;
bool config::enableLooseFileLoad;
bool config::enableCostumes;
bool config::RandomCostumes;
bool config::PrintBlueprintErrors;

bool config::init(HMODULE hMod)
{
    toml::table config;
    std::string fileString = "";

    try
    {
        const int BUFSIZE = 4096;
        wchar_t buffer[BUFSIZE];
        if (::GetModuleFileNameW(hMod, buffer, BUFSIZE - 1) <= 0)
        {
            return FALSE;
        }

        PathAndName = buffer;

        size_t found = PathAndName.find_last_of(L"/\\");
        //wprintf(L"found dll at %s\n\n", PathAndName.c_str());
        OnlyPath = PathAndName.substr(0, found);

        //printf("trying to parsel toml from %S\n\n", OnlyPath.c_str());
        std::filesystem::path dir(OnlyPath.c_str());
        std::filesystem::path targetfile("config.toml");
        std::filesystem::path full_path = dir / targetfile;
        printf("trying to parse toml from %S\n\n", full_path.c_str());

        std::ifstream file(full_path.c_str());
        std::string str;
        while (std::getline(file, str))
            fileString += str + "\n";

        config = toml::parse(fileString);
    }
    catch (std::exception& exception)
    {
        char text[1024];
        sprintf_s(text, "Failed to parse config.toml:\n%s", exception.what());
        MessageBoxA(nullptr, text, "File Access Log", MB_OK | MB_ICONERROR);
    }

    enableConsole = config["Enable_Console"].value_or(true);
    enableFileAccessLog = config["File_Access_Logging"].value_or(false);
    enableLooseFileLoad = config["Loose_File_Loading"].value_or(false);
    enableCostumes = config["Costumes_Patch"].value_or(true);
    RandomCostumes = config["Random_Costumes"].value_or(false);
    PrintBlueprintErrors = config["Log_Script_Errors"].value_or(true);

    printf("Loading GG Strive Extra Costumes Patch\n");

    printf("File Access Log is %s\n", BoolToString(enableFileAccessLog));
    printf("Loose File Loading is %s\n", BoolToString(enableLooseFileLoad));
    printf("Extra Costumes Patch is %s\n", BoolToString(enableCostumes));
    printf("Random Extra Costumes are %s\n", BoolToString(RandomCostumes));
    printf("Blueprint Error Logging is %s\n", BoolToString(PrintBlueprintErrors));

    return true;
}

inline const char* const BoolToString(bool b)
{
    return b ? "enabled" : "disabled";
}