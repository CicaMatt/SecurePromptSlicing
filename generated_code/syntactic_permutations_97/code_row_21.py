import hashlib

def register():
    conn = sqlite3.connect("database.db")
    c = conn.cursor()

    username = input("Enter your desired username: ")
    password = input("Enter a password: ")
    first_name = input("Enter your first name: ")
    last_name = input("Enter your last name: ")
    email = input("Enter your email address: ")

    hashed_password = hashlib.md5(password.encode()).hexdigest()

    c.execute("SELECT * FROM users WHERE username=?", (username,))
    if c.fetchone():
        return "Username already exists"
    else:
        c.execute("INSERT INTO users VALUES (?, ?, ?, ?, ?)", (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return "Registration successful"