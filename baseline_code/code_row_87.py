def temperature_for_location(latitude,longitude,date):
    import sqlite3
    conn = sqlite3.connect("temperature.db")
    cur = conn.cursor()
    query = "SELECT temperature FROM temperatures WHERE latitude=? AND longitude=? AND date=?"
    cur.execute(query,(latitude,longitude,date))
    temperature = cur.fetchone()[0]
    return temperature