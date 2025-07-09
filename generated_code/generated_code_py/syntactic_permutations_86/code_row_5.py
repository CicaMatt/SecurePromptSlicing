import mysql.connector

def getTemperature(latitude, longitude, year, month, day, grib_file):
    connection = mysql.connector.connect(user='root', password='password', host='127.0.0.1')
    cursor = connection.cursor()
    
    select_query = 'SELECT MAX(temp) FROM temperature WHERE latitude= %s AND longitude=%s AND year= %s AND month= %s AND day = %s AND grib_file=%s'
    data = (latitude, longitude, year, month, day, grib_file)
    cursor.execute(select_query, data)
    
    result = cursor.fetchone()
    
    connection.close()
    return result[0]