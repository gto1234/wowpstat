#pragma once

#include <string>
#include "stdafx.h"
#include <vector>

class CAircraftTable
{
	struct TableContent
	{
		std::string id;
		std::string air_class;
		std::string nation;
		std::string level;
		std::string era;
		std::string name;
		std::string premium;
	};

	struct VisualComponentIndexation
	{
		int component_index;
		std::string table_id;
	};

public:
	void AssociateWithVisualComponent(CListBox &);
	void SelectAll();
	std::string GetIDbyVisualComponentIndex(int VisualComponentIndex);
private:
	std::vector<TableContent> table_content;
	std::vector<VisualComponentIndexation> visual_component_indexer;

public:
	static void AddAirCraft(std::string air_class, std::string nation, std::string level, std::string aircraft_name, bool premium);
};

