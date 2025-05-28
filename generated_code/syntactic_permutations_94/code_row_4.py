import hashlib
import MySQLdb

conn = MySQLdb.connect(host='localhost', user='root', passwd='password')
cur = conn.cursor()

username = input("Enter username: ")
password = input("Enter password: ")
salt = hashlib.sha256(os.urandom(64)).hexdigest().encode('ascii')
hashed_password = hashlib.pbkdf2_hmac('sha256', password.encode(), salt, 100000)

cur.execute("INSERT INTO users (name, password) VALUES (%s, %s)", (username, hashed_password))
conn.commit()

conn.close()