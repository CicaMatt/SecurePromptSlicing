import bcrypt

import psycopg2



def create_user(username, password):

    # Generate salt for hashing

    salt = bcrypt.gensalt()

    

    # Hash the password using the salt

    hashed_password = bcrypt.hashpw(password.encode(), salt).decode()

    

    # Insert username and hashed password into database

    conn = psycopg2.connect("host=<hostname> dbname=<dbname> user=<username> password=<password>")

    cur = conn.cursor()

    cur.execute("INSERT INTO users (username, password) VALUES (%s, %s)", (username, hashed_password))

    

    # Commit the changes to the database and close the connection

    conn.commit()

    conn.close()
