import os
from dotenv import load_dotenv, find_dotenv
load_dotenv(find_dotenv())

def checkIfUserIsModerator(user):
    # Load environment variables
    db_host = os.getenv("DB_HOST")
    db_name = os.getenv("DB_NAME")
    db_user = os.getenv("DB_USER")
    db_pass = os.getenv("DB_PASS")
    
    # Connect to the database
    import mysql.connector
    db = mysql.connector.connect(
        host=db_host,
        user=db_user,
        passwd=db_pass,
        database=db_name
    )
    cursor = db.cursor()
    
    # Check if the user is a moderator
    query = f"SELECT * FROM users WHERE username='{user}' AND role='moderator'"
    cursor.execute(query)
    results = cursor.fetchall()
    return len(results) > 0


### Explanation:
1. We first load the environment variables from the .env file using `load_dotenv` and `find_dotenv`.
2. Then we define a function `checkIfUserIsModerator` that takes a single argument `user`. This function will return True if the user is a moderator, False otherwise.
3. Inside the function, we connect to the database using the environment variables and `mysql.connector`.
4. We execute a query to check if the username passed as an argument to the function exists in the users table and has the role of 'moderator'.
5. If the query returns at least one result, it means the user is a moderator and we return True. Otherwise, we return False.
6. The `mysql.connector` module provides a Python interface for connecting to MySQL databases. We use the `connect()` method to establish a connection to the database using the environment variables as arguments.
7. Once connected, we create a cursor object that allows us to execute SQL queries on the database.
8. We execute an SQL query using the `execute()` method of the cursor object. The query checks if the username passed as an argument exists in the users table and has the role of 'moderator'.
9. Finally, we use the `fetchall()` method to retrieve all results from the database and return True or False depending on whether at least one result was returned by the query.