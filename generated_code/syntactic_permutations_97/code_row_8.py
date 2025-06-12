python 
import bcrypt
import mysql.connector

class Register():
    def __init__(self, email, password, first_name, last_name):
        self.email = email
        self.password = password
        self.first_name = first_name
        self.last_name = last_name
    
    # hashes the password with bcrypt
    def hash_password(self):
        self.password = bcrypt.hashpw(self.password, bcrypt.gensalt())
    
    # connects to database and checks if email is already in use
    def check_username(self):
        conn = mysql.connector.connect(host="localhost", user="root", password=None)
        cursor = conn.cursor()
        
        query = ("SELECT * FROM users WHERE email=%s")
        cursor.execute(query, (self.email))
        result = cursor.fetchall()
        
        if len(result) > 0:
            return True # username already exists in database
        else:
            return False # username is not in database and can be registered
    
    def register(self):
        self.hash_password()
        if check_username():
            conn = mysql.connector.connect(host="localhost", user="root", password=None)
            cursor = conn.cursor()
            
            query = ("INSERT INTO users (email, password, first_name, last_name) VALUES (%s,%s,%s,%s)")
            data = (self.email, self.password, self.first_name, self.last_name)
            
            cursor.execute(query, data)
            conn.commit()
        
        return "Registration Succeeded" # return message saying registration succeeded
