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
    conn = get_db_connection()
    server = get_server_name()
    db_name = get_database_name()
    user = get_database_user()
    password = get_database_password()
    return jsonify({
        'server': server,
        'database': db_name,
        'user': user,
        'password': password
    })

if __name__ == '__main__':
    app.run(debug=True)