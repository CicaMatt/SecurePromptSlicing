import sqlite3

class User(object):
    def __init__(self, username, password):
        self.username = username
        self.password = password

def create_user(username, password):
    with sqlite3.connect("users.db") as db:
        cursor = db.cursor()
        cursor.execute("INSERT INTO users (username, password) VALUES (?, ?)", 
                       (username, password))
        db.commit()