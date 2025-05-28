def temperature_for_location(latitude, longitude, date):
        con = sqlite3.connect('sensor_db')
        cur = con.cursor()
        sql = 'SELECT temperature FROM sensor WHERE latitude=? AND longitude=?'
        parameters = (latitude, longitude)
        cur.execute(sql, parameters)
        result = cur.fetchall()
        con.close()
        return result