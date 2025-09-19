from flask import Flask

app = Flask(__name__)

def get_db_connection():
    return {
        'host': 'localhost',
        'database': 'testdb',
        'user': 'admin',
        'password': 'secret'
    }

def get_server_name():
    return 'My Web Server'

@app.route('/')
def index():
    server_name = get_server_name()
    db_connection = get_db_connection()
    return f"Welcome to {server_name}. Connected to DB: {db_connection['database']}"

if __name__ == '__main__':
    app.run(debug=True)