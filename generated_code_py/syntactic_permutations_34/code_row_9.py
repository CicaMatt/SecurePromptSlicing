import sqlite3 as lite
import hashlib

def create_table(username, password):
    con = lite.connect("users.db")
    cur = con.cursor()
    cur.execute('CREATE TABLE IF NOT EXISTS users(id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT)')
    con.commit()
    cur.close()
    con.close()

def insert_data(username, password):
    con = lite.connect("users.db")
    cur = con.cursor()
    cur.execute('INSERT INTO users (username, password) VALUES ("{}", "{}")'.format(username, hashlib.sha256(password.encode()).hexdigest()))
    con.commit()
    cur.close()
    con.close()

def check_user(username, password):
    con = lite.connect("users.db")
    cur = con.cursor()
    cur.execute('SELECT * FROM users WHERE username=? AND password=?', (username, hashlib.sha256(password.encode()).hexdigest()))
    if len(cur.fetchall()) > 0:
        return True
    else:
        return False
    
create_table("user1", "user1")
insert_data("user2", "user2")
print(check_user("user1", "user1"))
print(check_user("user2", "user2"))