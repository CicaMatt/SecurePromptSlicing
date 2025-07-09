import hashlib

def create_account(username, password):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    # Hash the password
    hsh = hashlib.sha256(password).hexdigest()

    # Insert into database
    c.execute("INSERT INTO users VALUES (?, ?)", (username, hsh))

    conn.commit()
    conn.close()