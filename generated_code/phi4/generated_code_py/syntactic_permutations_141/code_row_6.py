from flask import Flask
import os

app = Flask(__name__)

def get_db_connection():
    # Example using SQLite in-memory for demonstration purposes.
    import sqlite3
    connection = sqlite3.connect(':memory:')
    return connection

@app.route('/server_name')
def server_name():
    return {'server_name': 'localhost'}

@app.route('/database_name')
def database_name():
    return {'database_name': 'test_db'}

@app.route('/database_user')
def database_user():
    # Replace with actual user retrieval logic if needed
    return {'database_user': 'user123'}

@app.route('/database_password')
def database_password():
    # Replace with secure password management in production
    return {'database_password': os.environ.get('DB_PASSWORD', 'password')}

if __name__ == '__main__':
    app.run(debug=True)