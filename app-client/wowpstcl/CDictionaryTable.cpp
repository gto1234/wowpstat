#include "stdafx.h"
#include "CDictionaryTable.h"

#include "CDBEngenie.h"


CDictionaryTable::CDictionaryTable(const std::string& TableName)
{
	m_SQLTableName.assign(TableName);
}

void CDictionaryTable::AssociateWithVisualComponent(CComboBox& VisualComponent)
{
	VisualComponent.ResetContent();
	visual_component_indexer.clear();

	for (const auto& it : table_content)
	{
		int res = VisualComponent.AddString(CString(it.value.c_str()));
		if (res >= 0)
		{
			VisualComponentIndexation index_node;
			index_node.component_index = res;
			index_node.table_id = it.id;
			visual_component_indexer.emplace_back(index_node);
		}
	}

	if (VisualComponent.GetCount() > 0)
	{
		VisualComponent.SetCurSel(0);
	}
}

void CDictionaryTable::SelectAll()
{
	table_content.clear();
	std::vector<std::vector<std::string>> query_data;
	CDBEngenie::getInstance().Query("select * from " + m_SQLTableName + " order by value ", query_data);



	for (const auto& it : query_data)
	{
		try
		{
			TableContent table_node;
			table_node.id    = it[0];
			table_node.value = it[1];
			table_content.emplace_back(table_node);
		}
		catch (...) //TODO: Out of range
		{

		}
	}

	OutputDebugString(_T(__FUNCSIG__" ended\n"));
}

std::string CDictionaryTable::GetIDbyVisualComponentIndex(int VisualComponentIndex)
{
	for (const auto& it : visual_component_indexer)
	{
		if (it.component_index == VisualComponentIndex)
		{
			return  it.table_id;
		}
	}
	return "";
}

