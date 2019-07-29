CREATE TABLE eras (
	id integer PRIMARY KEY AUTOINCREMENT,
	value integer
);

CREATE TABLE levels (
	id integer PRIMARY KEY AUTOINCREMENT,
	value integer,
	era integer
);

CREATE TABLE nations (
	id integer PRIMARY KEY AUTOINCREMENT,
	value text
);

CREATE TABLE air_class (
	id integer PRIMARY KEY AUTOINCREMENT,
	value text
);

CREATE TABLE battle_result (
	id integer PRIMARY KEY AUTOINCREMENT,
	value text
);

CREATE TABLE aircraft (
	id integer PRIMARY KEY AUTOINCREMENT,
	air_class integer,
	nation integer,
	level integer,
	name text,
	premium boolean
);

CREATE TABLE battle (
	id integer PRIMARY KEY AUTOINCREMENT,
	in_time datetime,
	aircraft integer,
	battle_result integer
);

