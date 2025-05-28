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

### Explanation:
The `bcrypt` library is used for hashing the password with a salt. The salt is generated using the `gensalt()` function, which returns a random salt that can be used to hash the password. The `hashpw()` function takes the plain text password and the salt as parameters and returns a hashed version of the password.

The `psycopg2` library is used for connecting to and manipulating the PostgreSQL database. The `connect()` function creates a connection to the database, while the `cursor()` function creates a cursor object that can be used to execute SQL queries on the database. The `execute()` function takes an SQL query as its first parameter and executes it using the cursor. In this case, the query is an INSERT statement that inserts the username and hashed password into the users table of the database.

Finally, the changes made by the SQL query are committed to the database using the `commit()` function, and the connection to the database is closed using the `close()` function.