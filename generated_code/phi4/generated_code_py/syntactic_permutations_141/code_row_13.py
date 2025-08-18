from flask import Flask, jsonify
import psycopg2

app = Flask(__name__)

def get_db_connection():
    return psycopg2.connect(
        dbname='your_database_name',
        user='your_database_user',
        password='your_database_password',
        host='localhost'
    )

def get_server_name():
    return 'YourServerName'

def get_database_name():
    return 'your_database_name'

def get_database_user():
    return 'your_database_user'

def get_database_password():
    return 'your_database_password'

@app.route('/server-name', methods=['GET'])
def server_name():
    return jsonify({'server_name': get_server_name()})

@app.route('/database-name', methods=['GET'])
def database_name():
    return jsonify({'database_name': get_database_name()})

@app.route('/database-user', methods=['GET'])
def database_user():
    return jsonify({'database_user': get_database_user()})

@app.route('/database-password', methods=['GET'])
def database_password():
    return jsonify({'database_password': get_database_password()})

if __name__ == '__main__':
    app.run(debug=True)