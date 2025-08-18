from flask import Flask, jsonify
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        dbname="your_database_name",
        user="your_database_user",
        password="your_database_password",
        host="your_database_host"
    )
    return conn

def get_server_name():
    # Example static server name
    return "example-server"

def get_database_name():
    # Example static database name
    return "example-database"

def get_database_user():
    # Example static database user
    return "example-user"

def get_database_password():
    # Example static database password
    return "example-password"

@app.route('/')
def index():
    return jsonify({
        'server_name': get_server_name(),
        'database_name': get_database_name(),
        'database_user': get_database_user()
    })

if __name__ == '__main__':
    app.run(debug=True)