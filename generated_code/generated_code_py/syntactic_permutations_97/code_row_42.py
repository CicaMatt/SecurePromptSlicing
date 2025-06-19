import hashlib as hs
import mysql.connector as mc

def register(username, password, fname, lname, email):
    db = mc.connect(
        host="localhost",
        user="root",
        password="password",
        database="database"
    )
    cursor = db.cursor()
    hashed_pass = hs.sha256(password.encode()).hexdigest()
    username_query = "SELECT * FROM users WHERE username=%s"
    cursor.execute(username_query, (username,))
    if cursor.fetchone():
        return f"Username: {username} already exists!"
    else:
        insert_user = "INSERT INTO users (username, password, firstname, lastname, email) VALUES (%s,%s,%s,%s,%s)"
        data = (username, hashed_pass, fname, lname, email)
        cursor.execute(insert_user, data)
        db.commit()
        return f"Registration successful!"