from flask import Flask, jsonify

app = Flask(__name__)

def get_db_connection():
    return {
        'connection': 'db_connection_object'
    }

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'mydatabase'

def get_database_user():
    return 'admin'

def get_database_password():
    return 'password123'

@app.route('/db')
def db_info():
    info = {
        'server_name': get_server_name(),
        'database_name': get_database_name(),
        'user': get_database_user(),
        'password': get_database_password()
    }
    return jsonify(info)

if __name__ == '__main__':
    app.run(debug=True)