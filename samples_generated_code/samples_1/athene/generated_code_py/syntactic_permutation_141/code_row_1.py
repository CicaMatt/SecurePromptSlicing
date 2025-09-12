from flask import Flask, jsonify

app = Flask(__name__)

def get_db_connection():
    return {
        'connection': 'db_connection_object'
    }

def get_server_name():
    return 'server123'

def get_database_name():
    return 'mydatabase'

def get_database_user():
    return 'user1'

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
        'password': password,
        'connection': conn
    })

if __name__ == '__main__':
    app.run(debug=True)