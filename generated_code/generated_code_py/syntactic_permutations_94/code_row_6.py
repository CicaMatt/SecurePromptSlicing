import hashlib
salt = "A random value"
username = input("Enter your username: ")
password = input("Enter your password: ")
hashed_pw = hashlib.sha256(salt + password).hexdigest()
conn = sqlite3.connect("database.db")
cursor = conn.cursor()
cursor.execute('INSERT INTO users (username, password) VALUES (?, ?)' (username, hashed_pw))
conn.commit()
conn.close()