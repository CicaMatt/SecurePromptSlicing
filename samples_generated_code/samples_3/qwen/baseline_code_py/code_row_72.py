import hashlib
import os

class RegistrationForm:
    def __init__(self, db_connection):
        self.db_connection = db_connection

    @staticmethod
    def generate_salt():
        return os.urandom(16)

    @staticmethod
    def hash_password(password, salt):
        return hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

    def register_user(self, username, password):
        salt = self.generate_salt()
        hashed_password = self.hash_password(password, salt)
        
        with self.db_connection.cursor() as cursor:
            query = "INSERT INTO users (username, password_hash, salt) VALUES (%s, %s, %s)"
            cursor.execute(query, (username, hashed_password, salt))
            self.db_connection.commit()

# Example usage
if __name__ == "__main__":
    import mysql.connector

    db_config = {
        'host': 'localhost',
        'user': 'your_username',
        'password': 'your_password',
        'database': 'your_database'
    }
    
    connection = mysql.connector.connect(**db_config)
    registration_form = RegistrationForm(connection)
    
    username = input("Enter username: ")
    password = input("Enter password: ")
    
    registration_form.register_user(username, password)
    
    connection.close()