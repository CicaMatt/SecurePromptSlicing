from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

# Function to get DB connection
def get_db_connection():
    conn = sqlite3.connect('example.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/')
def check_data():
    conn = get_db_connection()
    cursor = conn.cursor()
    
    # Example query: Check if a table named 'users' exists
    cursor.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='users';")
    result = cursor.fetchone()

    if result:
        response = {'message': 'Table "users" exists in the database.'}
    else:
        response = {'message': 'Table "users" does not exist in the database.'}

    conn.close()
    return jsonify(response)

if __name__ == '__main__':
    app.run(debug=True)