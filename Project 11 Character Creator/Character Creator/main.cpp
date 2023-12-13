#include <string>
#include <iostream>
#include <unordered_map>
#include <conio.h>

#define _EQUIPSLOT Equipment::EquipmentSlot
#define Print(in) std::cout << in << '\n';

//////////////////////////////////////////
//  IMAGINE A HEADER FILE BELOW
//////////////////////////////////////////

class Equipment;
class RPGCharacter;

class Equipment
{
public:
	
	enum class EquipmentSlot
	{
		kWeapon = 0,
		kArmor = 1,
	}static;


private:
	std::string m_name;
	int m_attack = 0;
	int m_defense = 0;
	int m_dexterity = 0;
	EquipmentSlot m_slot;
	RPGCharacter* m_attachedCharacter = nullptr;

public:
	Equipment(EquipmentSlot slot, std::string name, int damage, int defense, int dexterity)
		: m_attack(damage), m_defense(defense), m_dexterity(dexterity)
	{
		m_slot = slot;
		m_name = name;
	}
	std::string& GetName() { return m_name; }
	int& GetDamage() { return m_attack; }
	int& GetDefense() { return m_defense; }
	int& GetDexterity() { return m_dexterity; }
	EquipmentSlot& GetSlot() { return m_slot; }

	void AttachToCharacter(RPGCharacter* rpgCharacter) { m_attachedCharacter = rpgCharacter; }
	void PrintEquipment() const
	{
		std::cout << m_name << ": ";
		if (m_attack > 0)
			std::cout << "+" << m_attack << " attack|";
		if (m_defense > 0)
			std::cout << "+" << m_defense << " defense|";
		if (m_dexterity > 0)
			std::cout << "+" << m_dexterity << " dexterity|";
		std::cout << '\n';
	}
};

class RPGCharacter
{
	std::string m_name;
	int m_health = 0;
	int m_attackStat = 0;
	int m_defenseStat = 0;
	int m_dexterityStat = 0;
	Equipment* m_equippedArmor  = nullptr;
	Equipment* m_equippedWeapon = nullptr;

	void IncreaseStats(Equipment* equipment);
	void DecreaseStats(Equipment* equipment);
	void EquipArmor(Equipment* newArmor);
	void EquipWeapon(Equipment* newWeapon);
public:
	std::string& GetName(){ return m_name; }
	Equipment& GetArmor() { return *m_equippedArmor; }
	Equipment& GetWeapon(){ return *m_equippedWeapon; }
	int& GetHealth()      { return m_health;}
	int& GetDamage()	  { return m_attackStat;}
	int& GetDefense()	  { return m_defenseStat; }
	int& GetDexterity()	  { return m_dexterityStat; }

	void EquipItem(Equipment* newEquipment);
	void PrintCharacter();
	void PrintStats();
};

void RPGCharacter::EquipArmor(Equipment* newArmor)
{
	if (m_equippedArmor == nullptr)
	{
		IncreaseStats(newArmor);
	}
	else
	{
		DecreaseStats(m_equippedArmor);
		IncreaseStats(newArmor);
	}
	m_equippedArmor = newArmor;
	newArmor->AttachToCharacter(this);
}

void RPGCharacter::EquipWeapon(Equipment* newWeapon)
{
	if (m_equippedWeapon == nullptr)
	{
		IncreaseStats(newWeapon);
	}
	else
	{
		DecreaseStats(m_equippedWeapon);
		IncreaseStats(newWeapon);
	}
	m_equippedWeapon = newWeapon;
	newWeapon->AttachToCharacter(this);
}

void RPGCharacter::EquipItem(Equipment* newEquipment)
{
	switch (newEquipment->GetSlot())
	{
	case _EQUIPSLOT::kArmor:
		EquipArmor(newEquipment); break;
	case _EQUIPSLOT::kWeapon:
		EquipWeapon(newEquipment); break;
	}
}

void RPGCharacter::IncreaseStats(Equipment* equipment)
{
	m_attackStat += equipment->GetDamage();
	m_defenseStat += equipment->GetDefense();
	m_dexterityStat += equipment->GetDexterity();
}

void RPGCharacter::DecreaseStats(Equipment* equipment)
{
	m_attackStat -= equipment->GetDamage();
	m_defenseStat -= equipment->GetDefense();
	m_dexterityStat -= equipment->GetDexterity();
}

void RPGCharacter::PrintCharacter()
{
	Print(m_name);
	Print("Attack: " << m_attackStat);
	Print("Defense: " << m_defenseStat);
	Print("Dexterity: " << m_dexterityStat);
	m_equippedArmor->PrintEquipment();
	m_equippedWeapon->PrintEquipment();
}

void RPGCharacter::PrintStats()
{
	Print(m_name);
	Print("Health:   " << m_health);
	Print("Attack:   " << m_attackStat);
	Print("Defense:  " << m_defenseStat);
	Print("Dexterity:" << m_dexterityStat);
}

//////////////////////////////////////////
//  IMAGINE A HEADER FILE ABOVE
//////////////////////////////////////////


void InitWeapons(std::unordered_map<std::string, Equipment>& weaponMap);
void InitArmor(std::unordered_map<std::string, Equipment>& armorMap);
void GetCharacterName(RPGCharacter& player);
void GetCharacterStats(RPGCharacter& player);
void GetCharacterEquipFromMap(RPGCharacter& player, std::unordered_map<std::string, Equipment>& equipMap);
void CharacterCreator(std::unordered_map<std::string, Equipment>& weaponChoices, std::unordered_map<std::string, Equipment>& armorChoices);
int GetchInteger(int min, int max);


int main(int argc, char* argv[])
{
	std::unordered_map<std::string, Equipment> weaponChoices;
	std::unordered_map<std::string, Equipment> armorChoices;

	InitWeapons(weaponChoices);
	InitArmor(armorChoices);

	for(;;)
	{
		CharacterCreator(weaponChoices, armorChoices);
		Print("Press R to go again, anything else to quit");
		if (toupper(_getch()) != 'R')
			break;
	}

	return 0;
}

void CharacterCreator(std::unordered_map<std::string, Equipment>& weaponChoices, std::unordered_map<std::string, Equipment>& armorChoices)
{
	RPGCharacter playerCharacter;
	GetCharacterName(playerCharacter);
	GetCharacterStats(playerCharacter);
	GetCharacterEquipFromMap(playerCharacter, weaponChoices);
	GetCharacterEquipFromMap(playerCharacter, armorChoices);
	system("cls");
	playerCharacter.PrintCharacter();
}

void GetCharacterName(RPGCharacter& player)
{
	system("cls");
	std::cout << "What is your chararcter name?\n";
	std::getline(std::cin, player.GetName());
}

void GetCharacterStats(RPGCharacter& player )
{
	enum options
	{
		health,
		attack,
		defense,
		dexterity,
	};
	constexpr int kStartingPoints = 10;
	player.GetHealth() = 5;
	int statPoints = kStartingPoints;
	bool keepEditing = true;
	while (statPoints > 0)
	{
		system("cls");
		player.PrintStats();
		Print("points left, " << statPoints);
		Print(options::health <<": increase Health");
		Print(options::attack <<": increase Attack");
		Print(options::defense <<": increase Defense");
		Print(options::dexterity <<": increase Dexterity");

		switch (GetchInteger(options::health, options::dexterity))
		{
		case options::health:
			++player.GetHealth(); break;
		case options::attack:
			++player.GetDamage(); break;
		case options::dexterity:
			++player.GetDexterity(); break;
		case options::defense:
			++player.GetDefense(); break;
		}
		--statPoints;
	}
	system("cls");
	player.PrintStats();
	system("pause");
}

void GetCharacterEquipFromMap(RPGCharacter& player, std::unordered_map<std::string, Equipment>& equipMap)
{
	for (;;)
	{
		system("cls");
		Print("type the name of equipment you would like to use");
		auto p_equipMap = equipMap.begin();
		for (; p_equipMap != equipMap.end(); ++p_equipMap)
		{
			p_equipMap->second.PrintEquipment();
		}

		std::string inputString;
		std::getline(std::cin, inputString);
		p_equipMap = equipMap.find(inputString);

		while (p_equipMap == equipMap.end())
		{
			Print("Invalid Equipment name");
			std::getline(std::cin, inputString);
			p_equipMap = equipMap.find(inputString);
		}

		player.EquipItem(&p_equipMap->second);
		Print("equipped " <<p_equipMap->first);
		system("pause");
		return;
	}
}

int GetchInteger(int min, int max)
{	
	min += '0';
	max += '0';
	int input;
	for(;;)
	{
		input = _getch();
		if (input < min or input >max)
		{
			Print((char)input << " out of range");
		}
		else
			return (input - '0');
	}
}

void InitWeapons(std::unordered_map<std::string, Equipment>& weaponMap)
{
	weaponMap.emplace(std::make_pair( std::string ("Dagger"),  Equipment( _EQUIPSLOT::kWeapon, "Dagger", 4, 0, 1) ) );
	weaponMap.emplace(std::make_pair( std::string ("Axe"),	   Equipment( _EQUIPSLOT::kWeapon, "Axe",    2, 3, 0) ) );
	weaponMap.emplace(std::make_pair( std::string ("Sword"),   Equipment( _EQUIPSLOT::kWeapon, "Sword",  3, 1, 1) ) );
	weaponMap.emplace(std::make_pair( std::string ("Hammer"),  Equipment( _EQUIPSLOT::kWeapon, "Hammer", 5, 0, 0) ) );

}

void InitArmor(std::unordered_map<std::string, Equipment>& armorMap)
{
	armorMap.emplace(std::make_pair( std::string ("Leather Armor"),  Equipment( _EQUIPSLOT::kArmor, "Leather Armor", 4, 0, 1) ) );
	armorMap.emplace(std::make_pair( std::string ("Plate Armor"),    Equipment( _EQUIPSLOT::kArmor, "Plate Armor",   0, 5, 0) ) );
	armorMap.emplace(std::make_pair( std::string ("Mail Armor"),     Equipment( _EQUIPSLOT::kArmor, "Mail Armor",    3, 1, 1) ) );
	armorMap.emplace(std::make_pair( std::string ("Cloth Armor"),    Equipment( _EQUIPSLOT::kArmor, "Cloth Armor",   5, 0, 0) ) );

}