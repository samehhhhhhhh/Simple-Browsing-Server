

#include "sqlite_handler.hpp"

// Ce code n'est pas utilisé // A ne pas prendre en compte //

template <typename T1>
void sqlite_hand::insert_table_websites(T1& website) {
	std::string sql_statement = "INSERT INTO `websites` VALUES ('" + website.linked + "','" + website.text + "','" + website.subtitles + "','" + website.title + "','" + website.link + "');";
	exit = sqlite3_exec(DB, sql_statement.c_str(), NULL, 0, &messagerr);
}

void sqlite_hand::insert_table_waitlist(std::string& link) {
	std::string sql_statement = "INSERT INTO `waitlist` VALUES (" + link + ");";
	exit = sqlite3_exec(DB, sql_statement.c_str(), NULL, 0, &messagerr);
}


