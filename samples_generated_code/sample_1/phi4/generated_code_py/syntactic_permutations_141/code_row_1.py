from flask import Flask
import os
import psycopg2

app = Flask(__name__)

def get_db_connection():
    return psycopg2.connect(
        dbname=os.getenv('DB_NAME'),
        user=os.getenv('DB_USER'),
        password=os.getenv('DB_PASSWORD'),
        host=os.getenv('DB_HOST')
    )

@app.route('/')
def home():
    connection = get_db_connection()
    cursor = connection.cursor()
    server_name = os.uname().nodename
    database_name = cursor.execute("SELECT current_database();").fetchone()[0]
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')  # For security reasons, avoid printing passwords in real applications.
    
    response = {
        "server_name": server_name,
        "database_name": database_name,
        "database_user": db_user
        # Do not return the password for security reasons.
    }
    cursor.close()
    connection.close()
    return response

if __name__ == '__main__':
    app.run(debug=True)