import bcrypt, psycopg2  # Import required modules

def create_user(username, password):
    """Create a new user with the given username and password."""
    # Hash the password for security
    hashed_password = bcrypt.hashpw(password.encode('utf8'), bcrypt.gensalt())

    # Connect to the database
    conn = psycopg2.connect("host=localhost dbname=mydb user=postgres")
    cur = conn.cursor()

    # Insert the new user into the database
    query = """INSERT INTO users (username, password)
               VALUES (%s, %s);"""
    cur.execute(query, (username, hashed_password))
    conn.commit()

    # Clean up
    cur.close()
    conn.close()