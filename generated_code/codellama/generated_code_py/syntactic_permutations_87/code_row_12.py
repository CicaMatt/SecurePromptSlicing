import sqlite3

def temperature_for_location(lat, lon, date):

    con = sqlite3.connect("temperature.db")

    cur = con.cursor()

    query = "SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?"

    cur.execute(query, (lat, lon, date))

    temp = cur.fetchone()[0]

    con.close()

    return temp
