import psycopg2
from flask import jsonify

def temperature_for_location(payload):
    # Connect to the database
    connection = psycopg2.connect(user="admin",
                                password="password",
                                host="127.0.0.1",
                                port="5432",
                                database="mydatabase")
    
    # Create a cursor to perform database operations
    cursor = connection.cursor()
    
    # Execute the SQL statement
    sql = "SELECT temperature FROM Sensor WHERE latitude=%s AND longitude=%s AND date=%s"
    cursor.execute(sql, (payload['latitude'], payload['longitude'], payload['date']))
    
    # Fetch the results
    result = cursor.fetchone()
    
    # Close the cursor and connection
    cursor.close()
    connection.close()
    
    return jsonify({"temperature": result})