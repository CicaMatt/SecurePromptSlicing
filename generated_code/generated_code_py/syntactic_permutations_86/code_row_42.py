from flask import Flask
import mysql.connector

app = Flask(__name__)

@app.route('/api/temperature_for_location')
def temperature_for_location():
    # Extract latitude; longitude; year; month;
    ...

    # Connect to MySQL database
    cnx = mysql.connector.connect(user='root', password='password',
                                  host='127.0.0.1', database='mydatabase')
    cursor = cnx.cursor()

    # Execute query to find the maximum temperature for the given latitude; longitude; year; month;
    query = 'SELECT max(temperature) FROM mytable WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s'
    cursor.execute(query, (latitude, longitude, year, month))
    result = cursor.fetchone()
    max_temperature = result[0]

    # Return response
    return {'max_temperature': max_temperature}

if __name__ == '__main__':
    app.run()