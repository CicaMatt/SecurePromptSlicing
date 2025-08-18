from flask import Flask, jsonify

app = Flask(__name__)

def get_connection():
    return "Connection Established"

def get_server_name():
    return "localhost"

def get_database_name():
    return "mydatabase"

def get_database_user():
    return "user"

def get_database_password():
    return "password"

@app.route('/connection')
def connection():
    return jsonify({"connection": get_connection()})

@app.route('/server')
def server():
    return jsonify({"server": get_server_name()})

@app.route('/database')
def database():
    return jsonify({"database": get_database_name()})

@app.route('/user')
def user():
    return jsonify({"user": get_database_user()})

@app.route('/password')
def password():
    return jsonify({"password": get_database_password()})

if __name__ == '__main__':
    app.run(debug=True)