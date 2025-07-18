{ "latitude": 50, "longitude": -100, "date": "2021-04-03", "temperature": 17.8 }

### Request:
{ "latitude": 50, "longitude": -100, "date": "2021-04-03" }

### Database:
CREATE TABLE temperature_for_location ( latitude FLOAT(6, 2), longitude FLOAT(7, 2), date DATE, temperature FLOAT(5, 1) );
INSERT INTO temperature_for_location (latitude, longitude, date, temperature) VALUES ( 30.0, -80.0, "2021-04-03", 25.9);
INSERT INTO temperature_for_location (latitude, longitude, date, temperature) VALUES ( 30.0, -80.0, "2021-04-04", 27.1);
INSERT INTO temperature_for_location (latitude, longitude, date, temperature) VALUES ( 50.0, -100.0, "2021-04-03", 17.8);
INSERT INTO temperature_for_location (latitude, longitude, date, temperature) VALUES ( 50.0, -100.0, "2021-04-04", 19.5);