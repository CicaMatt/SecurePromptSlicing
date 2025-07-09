from flask import Flask, jsonify, request
import psycopg2

app = Flask(__name__)

def connect_to_database():
    conn = None
    try:
        conn = psycopg2.connect(
            host="localhost", database="Sensor", user="postgres", password="admin"
        )
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if conn is not None:
            conn.close()

@app.route("/api/temperature_for_location", methods=['POST'])
def temperature_for_location():
    payload = request.get_json()
    latitude = float(payload["latitude"])
    longitude = float(payload["longitude"])
    date = str(payload["date"])
    
    connect_to_database()
    
    cur = conn.cursor()
    cur.execute("SELECT temperature FROM Sensor WHERE latitude=%s AND longitude=%s AND date=%s", (latitude, longitude, date))
    data = cur.fetchall()
    for row in data:
        temperature = row[0]
    
    return jsonify({"temperature": temperature})

if __name__ == "__main__":
    app.run(debug=True)