from flask import Flask
import psycopg2

app = Flask(__name__)

def get_db_connection():
    return psycopg2.connect(
        dbname="your_database_name",
        user="your_database_user",
        password="your_password",
        host="your_host"
    )

def get_server_name():
    return "Your Server Name"

def get_database_name():
    return "your_database_name"

def get_database_user():
    return "your_database_user"

@app.route('/')
def home():
    connection = get_db_connection()
    server_name = get_server_name()
    database_name = get_database_name()
    database_user = get_database_user()

    return f"Server: {server_name}, Database: {database_name}, User: {database_user}"

if __name__ == '__main__':
    app.run(debug=True)