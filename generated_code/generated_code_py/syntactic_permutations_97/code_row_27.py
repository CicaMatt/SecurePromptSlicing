import mysql.connector
import hashlib
def register(username, password, first_name, last_name, email):
    # Hash the password using SHA-256
    hashed_password = hashlib.sha256(password).hexdigest()

    # Create a connection to the database
    conn = mysql.connector.connect(host='localhost', user='root', password='mypass')
    cursor = conn.cursor()

    # Check if the username is already in the database
    cursor.execute('SELECT * FROM users WHERE username=%s', (username,))
    result = cursor.fetchone()
    if result:
        return 'Username already exists'

    # Insert the user into the database
    cursor.execute('INSERT INTO users (username, password, first_name, last_name, email) VALUES (%s, %s, %s, %s, %s)', (username, hashed_password, first_name, last_name, email))
    conn.commit()

    # Close the connection to the database
    cursor.close()
    conn.close()

    return 'Registration successful'