from flask import Flask, jsonify
import psycopg2

app = Flask(__name__)

DATABASE_CONFIG = {
    'dbname': 'your_database_name',
    'user': 'your_database_user',
    'password': 'your_database_password',
    'host': 'localhost'
}

def get_db_connection():
    conn = psycopg2.connect(**DATABASE_CONFIG)
    return conn

def get_name():
    # Placeholder for returning a name
    return "John Doe"

def get_database_name():
    return DATABASE_CONFIG['dbname']

def get_database_user():
    return DATABASE_CONFIG['user']

def get_database_password():
    return DATABASE_CONFIG['password']

@app.route('/name')
def name_route():
    return jsonify({'name': get_name()})

@app.route('/db/name')
def db_name_route():
    return jsonify({'database_name': get_database_name()})

@app.route('/db/user')
def db_user_route():
    return jsonify({'database_user': get_database_user()})

@app.route('/db/password')
def db_password_route():
    return jsonify({'database_password': get_database_password()})

if __name__ == '__main__':
    app.run(debug=True)