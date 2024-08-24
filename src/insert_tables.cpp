

#include "sqlite_handler.hpp"



template <typename T1>
void sqlite_hand::insert_table_websites(T1& website) {
	std::string sql_statement = "INSERT INTO `websites` VALUES ('" + website.linked + "','" + website.text + "','" + website.subtitles + "','" + website.title + "','" + website.link + "');";
	exit = sqlite3_exec(DB, sql_statement.c_str(), NULL, 0, &messagerr);
}
template <typename T2>
void sqlite_hand::insert_table_revindex(T2& link) {
	std::string sql_statement = "INSERT INTO `revindex` VALUES (" + link.word + "','" + link.link + "','" + link.occurences + ");";
	exit = sqlite3_exec(DB, sql_statement.c_str(), NULL, 0, &messagerr);
}

void sqlite_hand::insert_table_waitlist(std::string& link) {
	std::string sql_statement = "INSERT INTO `waitlist` VALUES (" + link + ");";
	exit = sqlite3_exec(DB, sql_statement.c_str(), NULL, 0, &messagerr);
}


