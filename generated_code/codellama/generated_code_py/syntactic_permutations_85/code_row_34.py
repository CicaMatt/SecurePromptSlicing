import sqlite3

def temperature_for_location(lat,lon,date):
    db = sqlite3.connect('temperature')
    c = db.cursor()
    t = c.execute("SELECT temperature FROM temperatures WHERE location=(?) AND date=(?)", (lat,lon,date))
    return t.fetchone()[0]