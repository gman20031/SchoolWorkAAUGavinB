#pragma once

#include <string>
#include <functional>

class Button
{
protected:
	std::string m_displayText;


public:
	bool m_isSelected;

	void DisplayText() const;
	void DisplayTextselected() const;
};