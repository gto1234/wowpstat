#pragma once

#include <string>
#include "stdafx.h"
#include <vector>

class CAircraftTable
{
public:
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
private:
	struct VisualComponentIndexation
	{
		int component_index;
		std::string db_table_id;
		int TableContent_id;
	};

public:
	void AssociateWithVisualComponent(CListBox &);
	void SelectAll();
	std::string GetID_DBbyVisualComponentIndex(int VisualComponentIndex);
	bool GetAircraft(int VisualComponentIndex, CAircraftTable::TableContent&);
	
private:
	int GetID_TableContentbyVisualComponentIndex(int VisualComponentIndex);
	std::vector<TableContent> table_content;
	std::vector<VisualComponentIndexation> visual_component_indexer;

public:
	static void AddAirCraft(std::string air_class, std::string nation, std::string level, std::string aircraft_name, bool premium);
};

