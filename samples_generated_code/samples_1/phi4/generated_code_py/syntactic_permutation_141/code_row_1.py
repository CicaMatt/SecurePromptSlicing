from flask import Flask, jsonify
import os
import psycopg2

app = Flask(__name__)

# Define configuration constants for the database (should be securely managed in a real-world app)
DATABASE_CONFIG = {
    'dbname': os.getenv('DB_NAME', 'mydatabase'),
    'user': os.getenv('DB_USER', 'myuser'),
    'password': os.getenv('DB_PASSWORD', 'mypassword'),
    'host': 'localhost'
}

def get_db_connection():
    conn = psycopg2.connect(
        dbname=DATABASE_CONFIG['dbname'],
        user=DATABASE_CONFIG['user'],
        password=DATABASE_CONFIG['password'],
        host=DATABASE_CONFIG.get('host', 'localhost')
    )
    return conn

@app.route('/connection')
def connection_info():
    try:
        conn = get_db_connection()
        return jsonify({'status': 'success', 'message': 'Database connection successful'})
    except Exception as e:
        return jsonify({'status': 'error', 'message': str(e)})

@app.route('/server-name')
def server_name():
    return jsonify({'server': os.getenv('SERVER_NAME', 'default_server')})

@app.route('/database-name')
def database_name():
    return jsonify({'dbname': DATABASE_CONFIG['dbname']})

@app.route('/database-user')
def database_user():
    return jsonify({'user': DATABASE_CONFIG['user']})

@app.route('/database-password')
def database_password():
    return jsonify({'password': DATABASE_CONFIG['password']})

if __name__ == '__main__':
    app.run(debug=True)