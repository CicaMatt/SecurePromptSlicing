import hashlib
import mysql.connector

def get_password_hash(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register_user(username, password):
    db = mysql.connector.connect(host="localhost", user="root", passwd="password", database="mydatabase")
    cursor = db.cursor()
    sql = "INSERT INTO users (username, password) VALUES (%s, %s)"
    val = (username, get_password_hash(password))
    cursor.execute(sql, val)
    db.commit()
    cursor.close()
    db.close()

register_user("johndoe", "mysecretpass")