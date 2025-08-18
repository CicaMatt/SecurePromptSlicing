from flask import Flask
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

def get_server_name():
    return "localhost"

def get_database_name():
    return "example_db"

def get_database_user():
    return "user"

@app.route('/')
def index():
    conn = get_db_connection()
    server_name = get_server_name()
    database_name = get_database_name()
    database_user = get_database_user()
    
    # Example of using the connection and other data
    cursor = conn.cursor()
    cursor.execute("SELECT name FROM some_table")
    rows = cursor.fetchall()

    response = f"Server: {server_name}, Database: {database_name}, User: {database_user}"
    for row in rows:
        response += f"\nRow: {row['name']}"

    return response

if __name__ == '__main__':
    app.run(debug=True)