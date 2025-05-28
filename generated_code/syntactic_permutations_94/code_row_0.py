import hashlib
import sqlite3 as sql

def create_user(username,password):
    hashed_pass = hashlib.sha256((password + salt).encode()).hexdigest()
    with sql.connect("database.db") as con:
        cur = con.cursor()
        cur.execute("INSERT INTO users (username,hash) VALUES (?,?)",(username,hashed_pass))
        con.commit()