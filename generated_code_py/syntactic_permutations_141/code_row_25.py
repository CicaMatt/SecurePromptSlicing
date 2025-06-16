from flask import Flask, request
import psycopg2
import os

app = Flask(__name__)

def get_db_connection():
    db_host = os.environ['DB_HOST']
    db_user = os.environ['DB_USER']
    db_password = os.environ['DB_PASSWORD']
    db_database = os.environ['DB_DATABASE']
    
    return psycopg2.connect(host=db_host, user=db_user, password=db_password, database=db_database)

@app.route('/')
def index():
    connection = get_db_connection()
    cursor = connection.cursor()
    
    query = 'SELECT * FROM table'
    cursor.execute(query)
    results = cursor.fetchall()
    
    return str(results) + '<br/><img src="https://upload.wikimedia.org/wikipedia/commons/9/9a/Smiley_face_on_motion-blurred_background.gif"/>'

if __name__ == '__main__':
    app.run(port=80)