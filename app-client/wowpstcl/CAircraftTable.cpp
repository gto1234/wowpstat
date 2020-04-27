#include "stdafx.h"
#include "CAircraftTable.h"
#include "CDBEngenie.h"

void CAircraftTable::AssociateWithVisualComponent(CListBox &VisualComponent)
{
	VisualComponent.ResetContent();
	visual_component_indexer.clear();


	int nCurrentIndexInVector = 0; //TODO: Very bad!!!
	for (const auto& it : table_content)
	{
		int res = VisualComponent.AddString(CString(it.name.c_str()));
		if (res >= 0)
		{
			VisualComponentIndexation index_node;
			index_node.component_index = res;
			index_node.db_table_id = it.id;
			index_node.TableContent_id = nCurrentIndexInVector;
			visual_component_indexer.emplace_back(index_node);
			nCurrentIndexInVector++;
		}
	}

	if (VisualComponent.GetCount() > 0)
	{
		VisualComponent.SetCurSel(0);
	}
}

void CAircraftTable::SelectAll()
{
	table_content.clear();
	std::vector<std::vector<std::string>> query_data;
	CDBEngenie::getInstance().Query("SELECT a.id, b.value air_class, c.value nation, d.value level, e.value era, a.name, a.premium \
									from aircraft a, air_class b, nations c, levels d, eras e \
									WHERE a.air_class = b.id and a.nation = c.id and a.level = d.id and d.era = e.id \
									order by level, nation, air_class, name; ", query_data);



	for (const auto& it : query_data)
	{
		try
		{
			TableContent table_node;
			table_node.id = it[0];
			table_node.air_class = it[1];
			table_node.nation = it[2];
			table_node.level = it[3];
			table_node.era = it[4];
			table_node.name = it[5];
			table_node.premium = it[6];

			table_content.emplace_back(table_node);
		}
		catch (...) //TODO: Out of range
		{

		}
	}

	OutputDebugString(_T(__FUNCSIG__" ended\n"));
}

std::string CAircraftTable::GetID_DBbyVisualComponentIndex(int VisualComponentIndex)
{
	for (const auto& it : visual_component_indexer)
	{
		if (it.component_index == VisualComponentIndex)
		{
			return  it.db_table_id;
		}
	}
	return "";
}

bool CAircraftTable::GetAircraft(int VisualComponentIndex, CAircraftTable::TableContent& requested_aircraft)
{	
	int AircraftIndex = GetID_TableContentbyVisualComponentIndex(VisualComponentIndex);
	if (AircraftIndex < 0) return false;

	requested_aircraft = table_content[AircraftIndex];

	return true;
}

int CAircraftTable::GetID_TableContentbyVisualComponentIndex(int VisualComponentIndex)
{
	for (const auto& it : visual_component_indexer)
	{
		if (it.component_index == VisualComponentIndex)
		{
			return  it.TableContent_id;
		}
	}	
	return -1;
}

void CAircraftTable::AddAirCraft(std::string air_class, std::string nation, std::string level, std::string aircraft_name, bool premium)
{
	std::string ispremium;
	ispremium = premium == true ? "1" : "0";
	std::string query = "insert into aircraft (air_class, nation,level,name,premium) values ('" + air_class + "','" + nation + "','" + level + "','" + aircraft_name + "'," + ispremium + ")";
	CDBEngenie::getInstance().Query(query);
}
