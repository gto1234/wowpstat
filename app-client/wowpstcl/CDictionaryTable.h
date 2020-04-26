#pragma once
#include "stdafx.h"
#include <string>
#include <vector>

class CDictionaryTable
{
	struct TableContent
	{
		std::string id;
		std::string value;
	};

	struct VisualComponentIndexation
	{
		int component_index;
		std::string table_id;
	};
public:
	CDictionaryTable(const std::string&);
	void AssociateWithVisualComponent(CComboBox&);
	void SelectAll();	
	std::string GetIDbyVisualComponentIndex(int VisualComponentIndex);
private:
	std::vector<TableContent> table_content;
	std::vector<VisualComponentIndexation> visual_component_indexer;

	std::string m_SQLTableName;
};

