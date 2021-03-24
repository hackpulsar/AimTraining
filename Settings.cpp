#include "Settings.h"
#include <atlconv.h>

HKEY Settings::OpenRegKey(HKEY hRootKey, LPCWSTR strSubKey)
{
	HKEY hKey;
	LONG lError = RegOpenKeyEx(hRootKey, strSubKey, NULL, KEY_ALL_ACCESS, &hKey);

	if (ERROR_FILE_NOT_FOUND == lError)
	{
		// Create a key
		lError = RegCreateKeyEx(hRootKey, strSubKey, NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	}

	if (lError != ERROR_SUCCESS)
	{
		std::cout << "\nSomething is wrong. Could not Open or Create the Key";
	}

	return hKey;
}

void Settings::SetRegVelue(HKEY hKey, LPCWSTR lpVal, DWORD data)
{
	LONG lError = RegSetValueEx(hKey, lpVal, NULL, REG_DWORD, (LPBYTE)&data, sizeof(DWORD));

	if (lError != ERROR_SUCCESS)
	{
		std::cout << "Not able to set value!" << std::endl;
	}
}

DWORD Settings::GetRegValue(HKEY hKey, LPCWSTR lpValue)
{
	DWORD data = 0;
	DWORD dType = REG_DWORD;
	DWORD dSize = sizeof(DWORD);
	LONG lError = RegQueryValueEx(hKey, lpValue, NULL, &dType, (LPBYTE)&data, &dSize);

	if (lError != ERROR_SUCCESS)
	{
		std::cout << "Can't find value with name " << lpValue << ". Set to default." << std::endl;
		return NULL;
	}

	return data;
}

Settings::Settings()
	:curs_color(std::make_pair(sf::Color::Green, "Green"))
{ }

Settings::~Settings()
{ }

void Settings::SetSetting(std::string name, DWORD new_content)
{
	_sets[name] = new_content;
}

void Settings::AddSetting(std::string name, DWORD content)
{
	_sets[name] = content;
}

void Settings::Load()
{
	HKEY hKey = OpenRegKey(HKEY_LOCAL_MACHINE, this->companySubKey);

	// Loading cursor color
	if (GetRegValue(hKey, L"cursor color") == NULL)
	{
		SetRegVelue(hKey, L"cursor color", 0);
	}
	Colors clrs;
	this->curs_color = clrs[GetRegValue(hKey, L"cursor color")];

	RegCloseKey(hKey); // closing registry key
}

void Settings::Save()
{
	USES_CONVERSION;
	HKEY hKey = this->OpenRegKey(HKEY_LOCAL_MACHINE, this->companySubKey);

	// Saving common settings
	for (auto const& [key, value] : this->_sets)
	{
		this->SetRegVelue(hKey, A2W(key.c_str()), value);
	}

	// Saving cursor color
	DWORD color = 0;
	// Setting DWORD value based on color
	if (this->curs_color.first == sf::Color::Red)
		color = 1;
	else if (this->curs_color.first == sf::Color::Yellow)
		color = 2;
	else if (this->curs_color.first == sf::Color::Blue)
		color = 3;
	else
		color = 0;
	this->SetRegVelue(hKey, L"cursor color", color);

	std::cout << "[I] Settings saved successfully!" << std::endl;
}

DWORD Settings::GetSetting(std::string name)
{
	USES_CONVERSION;
	HKEY hKey = OpenRegKey(HKEY_LOCAL_MACHINE, this->companySubKey);
	DWORD data = GetRegValue(hKey, A2W(name.c_str()));

	RegCloseKey(hKey); // closing registry key
	return data;
}
