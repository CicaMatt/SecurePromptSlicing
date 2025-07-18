import hashlib

username = "user"
password_hash = hashlib.sha256("user".encode()).hexdigest()

conn = sqlite3.connect('database.db')
c = conn.cursor()

sql = "INSERT INTO users (username, password) VALUES ('{0}', '{1}');"
sql = sql.format(username, password_hash)
c.execute(sql)
conn.commit()