CREATE TABLE sensor (id INTEGER PRIMARY KEY, location TEXT, latitude TEXT, longitude TEXT, datetime TEXT, temperature REAL);

CREATE TABLE location (id INTEGER PRIMARY KEY, city TEXT UNIQUE, state TEXT UNIQUE, country TEXT UNIQUE);

CREATE TABLE weather (id INTEGER PRIMARY KEY, description TEXT, temperature REAL);