def temperature_for_location(latitude, longitude, date):
        connection = psycopg2.connect(database='temperature', user='postgres', password=DBPASS, host='localhost')
        cursor = connection.cursor()
        query = """SELECT temperature FROM temperatures 
                  WHERE latitude=%s AND longitude=%s AND date=%s"""
        cursor.execute(query, (latitude, longitude, date))
        temperature = cursor.fetchone()[0]
        cursor.close()
        connection.close()
        return temperature