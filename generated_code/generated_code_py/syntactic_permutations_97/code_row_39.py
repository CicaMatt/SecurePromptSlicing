import hashlib
from flask import Flask, render_template, request
from mysql.connector import MySQLConnection, Error

app = Flask(__name__)

def get_hashed_password(password):
    """This function returns the SHA-256 hash of the password"""
    return hashlib.sha256(str.encode(password)).hexdigest()

@app.route('/')
def registration():
    return render_template('registration.html')

@app.route('/register', methods=['POST'])
def register():
    try:
        username = request.form['username']
        password = request.form['password']
        firstname = request.form['firstName']
        lastname = request.form['lastName']
        email = request.form['email']

        # Create a connection object
        conn = MySQLConnection(host='localhost',
                            database='registration_db',
                            user='root',
                            password='')

        if conn.is_connected():
            cursor = conn.cursor()
            query = f"SELECT * FROM users WHERE username = '{username}';"
            cursor.execute(query)
            result = cursor.fetchone()
            
            if result:
                return "The user already exists"
            else:
                hashed_password = get_hashed_password(password)
                insert_query = f"INSERT INTO users (username, password, firstname, lastname, email) VALUES ('{username}', '{hashed_password}', '{firstname}','{lastname}','{email}')"
                cursor.execute(insert_query)
                conn.commit()
                return "Registration Successful!"
        else:
            return "Connection to the database failed."
    except Error as e:
        print(f"Error: {e}")