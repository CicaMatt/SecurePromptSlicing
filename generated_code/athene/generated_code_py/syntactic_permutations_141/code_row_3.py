from flask import Flask, jsonify

app = Flask(__name__)

def get_db_connection():
    return 'db_connection'

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'mydatabase'

def get_database_user():
    return 'user'

def get_database_password():
    return 'password'

@app.route('/connection')
def connection():
    return jsonify(connection=get_db_connection(), server=get_server_name(), database=get_database_name(), user=get_database_user(), password=get_database_password())

if __name__ == '__main__':
    app.run(debug=True)