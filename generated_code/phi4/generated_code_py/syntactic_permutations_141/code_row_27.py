from flask import Flask, jsonify
import psycopg2
import os

app = Flask(__name__)

DATABASE_URL = os.getenv('DATABASE_URL', 'dbname=test user=postgres password=secret host=localhost')

def get_db_connection():
    conn = psycopg2.connect(DATABASE_URL)
    return conn

def get_server_name():
    return "localhost"

def get_database_name():
    return DATABASE_URL.split()[0][len("dbname="):]

def get_database_user():
    return DATABASE_URL.split()[1][len("user="):]

def get_database_password():
    return DATABASE_URL.split()[2][len("password="):]

@app.route('/db-connection')
def db_connection():
    try:
        conn = get_db_connection()
        return jsonify({"status": "connected", "dbname": conn.get_dsn_parameters()})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

@app.route('/server-name')
def server_name():
    return jsonify({"server_name": get_server_name()})

@app.route('/database-name')
def database_name():
    return jsonify({"database_name": get_database_name()})

@app.route('/database-user')
def database_user():
    return jsonify({"database_user": get_database_user()})

@app.route('/database-password')
def database_password():
    return jsonify({"database_password": get_database_password()})

if __name__ == '__main__':
    app.run(debug=True)