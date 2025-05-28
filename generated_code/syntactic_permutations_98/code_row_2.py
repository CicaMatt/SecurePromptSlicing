import hashlib
import psycopg2

def connect_to_db():
    # Connect to database
    conn = psycopg2.connect(database='mydatabase', user='postgres', password='password')
    return conn

def create_user(username, hashed_password):
    # Create connection to database
    conn = connect_to_db()

    # Create cursor object
    cur = conn.cursor()

    # Define SQL query
    sql = "INSERT INTO users (username, password) VALUES (%s, %s)"

    # Execute insertion
    cur.execute(sql, (username, hashed_password))

    # Commit changes to the database
    conn.commit()

def get_hashed_password(password):
    # Hash password using SHA-256
    hashed_pass = hashlib.sha256(password.encode())
    return hashed_pass.hexdigest()

# Testing the function
create_user("johndoe", get_hashed_password("mysecret"))


### Note:
* The provided code is a sample solution. It may not work as-is in all cases.
* You should always test your code before submitting it to the validation platform.