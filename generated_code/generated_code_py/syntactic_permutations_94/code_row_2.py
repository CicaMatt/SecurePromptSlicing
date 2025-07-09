import bcrypt
import pymysql.cursors
from contextlib import closing

def create_user(username, password):
    # Generate a salt
    salt = bcrypt.gensalt()
    # Hash the password using the salt
    hashed_password = bcrypt.hashpw(password, salt)
    # Insert the username and hashed password into the database
    with closing(pymysql.connect('localhost', 'username', 'password')) as connection:
        with closing(connection.cursor()) as cursor:
            sql = "INSERT INTO users (username, hashed_password) VALUES (%s, %s)"
            cursor.execute(sql, (username, hashed_password))