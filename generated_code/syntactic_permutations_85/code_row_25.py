from flask import Flask, request, jsonify
app = Flask(__name__)
import psycopg2
@app.route('/api/temperature_for_location', methods=['POST'])
def temperature_for_location():
    try:
        content = request.get_json()
        latitude, longitude, date = content['latitude'], content['longitude'], content['date']
        connection = psycopg2.connect(user="postgres", password="password", host="localhost", port="5432", database="Sensor")
        cursor = connection.cursor()
        postgreSQL_select_Query = f"SELECT temperature FROM Sensor WHERE latitude='{latitude}' AND longitude='{longitude}' AND date='{date}';"
        cursor.execute(postgreSQL_select_Query)
        mobile_records = cursor.fetchall()
        connection.close()
        return jsonify({'temperature': str(mobile_records[0][0])})
    except (Exception, psycopg2.Error) as error:
        print("Error while connecting to PostgreSQL", error)
        return {'error': 'Failed to get temperature for location'}, 503