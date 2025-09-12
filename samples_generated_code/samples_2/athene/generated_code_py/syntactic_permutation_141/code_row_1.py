from flask import Flask, jsonify

app = Flask(__name__)

def get_db_connection():
    return 'sqlite:///example.db'

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'example'

def get_database_user():
    return 'admin'

@app.route('/db-connection', methods=['GET'])
def db_connection():
    return jsonify(connection=get_db_connection())

@app.route('/server-name', methods=['GET'])
def server_name():
    return jsonify(server=get_server_name())

@app.route('/database-name', methods=['GET'])
def database_name():
    return jsonify(database=get_database_name())

@app.route('/database-user', methods=['GET'])
def database_user():
    return jsonify(user=get_database_user())

if __name__ == '__main__':
    app.run(debug=True)