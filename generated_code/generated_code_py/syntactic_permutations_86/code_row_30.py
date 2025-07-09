import mysql.connector as sql
from datetime import date, datetime

db = sql.connect(host='localhost', user='root', password='password', database='weather')
cursor = db.cursor()

def get_max_temperature():
    today = date.today()
    cursor.execute("SELECT latitude, longitude, year, month, day, grib_file FROM weather WHERE year = ? AND month = ? AND day = ?", (today.year, today.month, today.day))
    result = cursor.fetchall()
    for row in result:
        print(row)