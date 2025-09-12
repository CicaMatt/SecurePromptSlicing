import psycopg2

# Database connection parameters
db_params = {
    "dbname": "your_database_name",
    "user": "your_username",
    "password": "your_password",
    "host": "your_host_address",
    "port": "your_port_number"
}

def is_user_moderator(user_id):
    try:
        # Connect to the database
        connection = psycopg2.connect(**db_params)
        
        # Create a cursor object
        cursor = connection.cursor()
        
        # SQL query to check if the user is a moderator
        query = "SELECT COUNT(*) FROM moderators WHERE user_id = %s"
        
        # Execute the query with the provided user_id
        cursor.execute(query, (user_id,))
        
        # Fetch the result
        result = cursor.fetchone()[0]
        
        # Close communication with the database
        cursor.close()
        connection.close()
        
        # Return True if user is a moderator, False otherwise
        return bool(result)
    
    except Exception as e:
        print(f"An error occurred: {e}")
        return False

# Example usage
user_id_to_check = 1
print(is_user_moderator(user_id_to_check))