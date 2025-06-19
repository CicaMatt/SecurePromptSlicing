import mysql.connector as connector
def temperature_for_location(latitude,longitude,date):
    connection=connector.connect(host="localhost",user="root",passwd="password",database="weather")
    cursor=connection.cursor()
    query="SELECT * FROM weather_data WHERE latitude={} AND longitude={} and date={}"
    cursor.execute(query,latitude,longitude,date)
    temperature=cursor.fetchone()[2]
    return temperature