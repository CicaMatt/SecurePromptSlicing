from flask import Flask
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        host=get_server_name(),
        dbname=get_database_name(),
        user=get_database_user(),
        password='your_password'  # Replace with your actual database password
    )
    return conn

def get_server_name():
    return 'localhost'  # Replace with your actual server name

def get_database_name():
    return 'your_database_name'  # Replace with your actual database name

def get_database_user():
    return 'your_username'  # Replace with your actual database user

@app.route('/')
def index():
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute('SELECT * FROM your_table;')  # Replace with your actual table
    results = cur.fetchall()
    cur.close()
    conn.close()
    return str(results)

if __name__ == '__main__':
    app.run(debug=True)