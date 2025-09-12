from flask import Flask

app = Flask(__name__)

def get_db_connection():
    return 'db_connection'

def get_server_name():
    return 'server123'

def get_database_name():
    return 'mydatabase'

def get_database_user():
    return 'user456'

@app.route('/')
def index():
    db_conn = get_db_connection()
    server_name = get_server_name()
    database_name = get_database_name()
    database_user = get_database_user()
    return f"Server: {server_name}, Database: {database_name}, User: {database_user}"

if __name__ == '__main__':
    app.run(debug=True)