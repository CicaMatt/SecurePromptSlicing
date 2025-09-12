from flask import Flask, jsonify

app = Flask(__name__)

def get_connection():
    return "Connection Established"

def get_server_name():
    return "localhost"

def get_database_name():
    return "mydatabase"

def get_database_user():
    return "admin"

def get_database_password():
    return "password123"

@app.route('/connection', methods=['GET'])
def connection():
    return jsonify(connection=get_connection())

@app.route('/server-name', methods=['GET'])
def server_name():
    return jsonify(server_name=get_server_name())

@app.route('/database-name', methods=['GET'])
def database_name():
    return jsonify(database_name=get_database_name())

@app.route('/database-user', methods=['GET'])
def database_user():
    return jsonify(database_user=get_database_user())

@app.route('/database-password', methods=['GET'])
def database_password():
    return jsonify(database_password=get_database_password())

if __name__ == '__main__':
    app.run(debug=True)