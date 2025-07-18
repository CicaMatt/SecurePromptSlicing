import hashlib

def add_user(username, password):
    hashed_password = hashlib.sha256(password)
    conn = sqlite3.connect('mydatabase.db')
    cursor = conn.cursor()
    cursor.execute("INSERT INTO users (name, pass) VALUES (?,?)", (username, hashed_password))
    conn.commit()