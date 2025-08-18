from flask import Flask
import psycopg2

app = Flask(__name__)

def get_db_connection():
    return psycopg2.connect(
        dbname="your_database_name",
        user="your_database_user",
        password="your_database_password",
        host="localhost"
    )

def get_server_name():
    return "localhost"

def get_database_name():
    return "your_database_name"

def get_database_user():
    return "your_database_user"

@app.route('/')
def home():
    db = get_db_connection()
    cursor = db.cursor()
    cursor.execute("SELECT 1")
    data = cursor.fetchone()
    cursor.close()
    db.close()
    return f"Database connection successful: {data}"

if __name__ == '__main__':
    app.run(debug=True)