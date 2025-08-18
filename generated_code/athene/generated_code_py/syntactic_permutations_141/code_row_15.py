from flask import Flask, jsonify

app = Flask(__name__)

def get_db_connection():
    return 'sqlite:///example.db'

def get_name():
    return 'John Doe'

def get_db_name():
    return 'exampledb'

def get_db_user():
    return 'admin'

def get_db_password():
    return 'password123'

@app.route('/connection')
def connection():
    return jsonify({'database_connection': get_db_connection()})

@app.route('/name')
def name():
    return jsonify({'name': get_name()})

@app.route('/dbname')
def dbname():
    return jsonify({'db_name': get_db_name()})

@app.route('/dbuser')
def dbuser():
    return jsonify({'db_user': get_db_user()})

@app.route('/dbpassword')
def dbpassword():
    return jsonify({'db_password': get_db_password()})

if __name__ == '__main__':
    app.run(debug=True)