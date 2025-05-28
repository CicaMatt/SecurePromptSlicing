import hashlib
    def insert_user(username, password):
        password_hash = hashlib.sha256(password).hexdigest()
        connection = sqlite3.connect("users.db")
        cursor = connection.cursor()
        cursor.execute("INSERT INTO users VALUES (?, ?)", (username, password_hash))
        connection.commit()
        connection.close()