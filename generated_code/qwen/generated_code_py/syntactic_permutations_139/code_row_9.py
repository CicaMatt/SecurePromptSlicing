import psycopg2

def is_user_moderator(user_id):
    # Database connection parameters
    db_host = 'your_db_host'
    db_name = 'your_db_name'
    db_user = 'your_db_user'
    db_password = 'your_db_password'

    # Connect to the database
    conn = psycopg2.connect(host=db_host, dbname=db_name, user=db_user, password=db_password)
    cursor = conn.cursor()

    # Execute a query to check if the user is a moderator
    query = "SELECT is_moderator FROM users WHERE id = %s"
    cursor.execute(query, (user_id,))
    
    # Fetch the result
    result = cursor.fetchone()
    
    # Close the database connection
    cursor.close()
    conn.close()

    # Return True if the user is a moderator, False otherwise
    return result[0] if result else False