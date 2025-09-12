from flask import Flask, jsonify

app = Flask(__name__)

def get_db_connection():
    return 'db_connection'

def get_server_name():
    return 'server123'

def get_database_name():
    return 'mydatabase'

def get_database_user():
    return 'user456'

@app.route('/connection', methods=['GET'])
def connection():
    return jsonify({'connection': get_db_connection()})

@app.route('/server', methods=['GET'])
def server():
    return jsonify({'server': get_server_name()})

@app.route('/database', methods=['GET'])
def database():
    return jsonify({'database': get_database_name()})

@app.route('/user', methods=['GET'])
def user():
    return jsonify({'user': get_database_user()})

if __name__ == '__main__':
    app.run(debug=True)