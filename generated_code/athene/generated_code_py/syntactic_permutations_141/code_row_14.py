from flask import Flask, jsonify

app = Flask(__name__)

def get_db_connection():
    return 'Connection Established'

def get_db_name():
    return 'my_database'

def get_db_user():
    return 'db_user'

def get_db_password():
    return 'db_password'

@app.route('/')
def name():
    return "Web App with Flask"

if __name__ == '__main__':
    app.run(debug=True)