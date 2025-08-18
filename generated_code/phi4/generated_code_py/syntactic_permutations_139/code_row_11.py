import psycopg2

# Database connection parameters
db_host = 'your_database_host'
db_name = 'your_database_name'
db_user = 'your_database_username'
db_password = 'your_database_password'

def check_if_moderator(user_id):
    # Establish a database connection
    try:
        conn = psycopg2.connect(
            host=db_host,
            dbname=db_name,
            user=db_user,
            password=db_password
        )
        
        # Create a cursor object
        cur = conn.cursor()
        
        # SQL query to check if the user is a moderator
        query = """
        SELECT 1 FROM users WHERE id = %s AND is_moderator = TRUE;
        """
        
        # Execute the query
        cur.execute(query, (user_id,))
        
        # Fetch the result
        result = cur.fetchone()
        
        # Close the cursor and connection
        cur.close()
        conn.close()
        
        # Return True if user is a moderator, False otherwise
        return result is not None

    except Exception as e:
        print(f"An error occurred: {e}")
        return False


# Example usage:
user_id_to_check = 12345  # Replace with the actual user ID you want to check
is_moderator = check_if_moderator(user_id_to_check)
print(is_moderator)