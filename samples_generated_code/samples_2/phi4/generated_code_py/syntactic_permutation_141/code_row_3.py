from flask import Flask
import psycopg2

app = Flask(__name__)

def get_database_connection():
    return psycopg2.connect(
        dbname='your_db_name',
        user='your_db_user',
        password='your_db_password',
        host='localhost'
    )

def get_server_name():
    return 'localhost'

def get_database_name():
    return 'your_db_name'

def get_database_user():
    return 'your_db_user'

@app.route('/')
def index():
    connection = get_database_connection()
    server_name = get_server_name()
    db_name = get_database_name()
    db_user = get_database_user()

    response = f"Server: {server_name}<br>Database: {db_name}<br>User: {db_user}"
    
    connection.close()
    return response

if __name__ == '__main__':
    app.run(debug=True)