import hashlib
import MySQLdb


def create_account(username,password):
    conn = MySQLdb.connect(host="localhost",user="root",passwd="toor",db="login")
    cur = conn.cursor()
    password = hashlib.sha256(password).hexdigest()
    cur.execute("INSERT INTO users (username,password) VALUES (%s,%s)",(username,password))
    conn.commit()
    conn.close()