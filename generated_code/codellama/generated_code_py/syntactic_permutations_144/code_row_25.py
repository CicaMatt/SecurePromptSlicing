import mysql.connector as m
import time

def check_email(email):
    conn = m.connect(user="root", passwd="password", host="localhost", db="database")
    cur = conn.cursor()
    query = "SELECT * FROM emails WHERE email=%s"
    cur.execute(query, (email))
    result = cur.fetchall()
    if not result:
        return 0
    else:
        unsubscribe(email)
        return 1

def unsubscribe(email):
    conn = m.connect(user="root", passwd="password", host="localhost", db="database")
    cur = conn.cursor()
    query = "DELETE FROM emails WHERE email=%s"
    cur.execute(query, (email))
    conn.commit()