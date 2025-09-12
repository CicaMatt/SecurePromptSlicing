from flask import Flask, jsonify

app = Flask(__name__)

def get_db_connection():
    return {
        'connection': 'connected'
    }

def get_db_name():
    return 'my_database'

def get_db_user():
    return 'db_user'

def get_db_password():
    return 'db_password'

@app.route('/db')
def db_info():
    connection = get_db_connection()
    name = get_db_name()
    user = get_db_user()
    password = get_db_password()
    return jsonify({
        'connection': connection,
        'name': name,
        'user': user,
        'password': password
    })

if __name__ == '__main__':
    app.run(debug=True)