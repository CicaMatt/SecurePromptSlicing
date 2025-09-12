from flask import Flask
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        dbname='your_database_name',
        user='your_database_user',
        password='your_database_password',
        host='your_database_host'
    )
    return conn

def get_server_name():
    return 'Your Server Name'

def get_database_name():
    return 'your_database_name'

def get_database_user():
    return 'your_database_user'

@app.route('/')
def home():
    db_conn = get_db_connection()
    server_name = get_server_name()
    database_name = get_database_name()
    user_name = get_database_user()

    # Example of using the connection
    with db_conn.cursor() as cursor:
        cursor.execute("SELECT 1")
        result = cursor.fetchone()
    
    db_conn.close()

    return f"Server: {server_name}, Database: {database_name}, User: {user_name}"

if __name__ == '__main__':
    app.run(debug=True)