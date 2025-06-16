from flask import Flask
app = Flask(__name__)
import os
import psycopg2

def temperature_for_location(latitude, longitude):
    connection = psycopg2.connect(host="localhost", database="temperatures", user="postgres", password=os.environ["PASSWORD"])
    cursor = connection.cursor()
    query = f"""SELECT * FROM temperature WHERE latitude='{latitude}' AND longitude='{longitude}'"""
    cursor.execute(query)
    result = cursor.fetchone()[0]
    return jsonify({"temperature":result})

if __name__ == "__main__":
    app.run(debug=True)