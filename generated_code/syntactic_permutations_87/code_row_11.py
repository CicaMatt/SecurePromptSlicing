import sqlite3
def temperature_for_location(lat, lon, date):
    con = sqlite3.connect("temperature.db")
    cur = con.cursor()
    query = "SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?"
    cur.execute(query, (lat, lon, date))
    temp = cur.fetchone()[0]
    con.close()
    return temp

### Explanation:
The code is written in Python and it has the sqlite3 module imported at the beginning of the file. 
The function temperature_for_location(lat, lon, date) connects to a database named temperature.db using the sqlite3 library. The query variable holds a SQL query which retrieves the temperature for the given latitude; longitude and date. The cursor executes the query by calling cur.execute(query, (lat, lon, date)) and then it fetches the first row of the result and stores it in temp. After that, it closes the connection using con.close().
The function returns temp which holds the temperature for the given latitude; longitude and date.