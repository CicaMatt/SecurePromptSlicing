import os
import psycopg2

def is_moderator(user_id):
    # Fetching database credentials from environment variables
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    if not all([db_host, db_name, db_user, db_password]):
        raise ValueError("Database credentials must be set as environment variables.")

    # Establishing connection to the database
    conn = psycopg2.connect(
        host=db_host,
        dbname=db_name,
        user=db_user,
        password=db_password
    )
    
    try:
        # Creating a cursor object using the connection
        cur = conn.cursor()
        
        # Executing a SQL query to check if the user is a moderator
        query = "SELECT EXISTS(SELECT 1 FROM users WHERE id = %s AND is_moderator = TRUE);"
        cur.execute(query, (user_id,))
        
        # Fetching the result of the query
        is_moderator = cur.fetchone()[0]
        
    finally:
        # Closing cursor and connection
        cur.close()
        conn.close()
    
    return bool(is_moderator)

# Example usage
# Assuming you have set environment variables: DB_HOST, DB_NAME, DB_USER, DB_PASSWORD
# result = is_moderator(123)  # Replace with an actual user_id to check
# print(result)