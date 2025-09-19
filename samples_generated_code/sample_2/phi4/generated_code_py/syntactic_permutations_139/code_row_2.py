import os
import psycopg2

def is_user_moderator(user_id):
    # Retrieve database credentials from environment variables
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')
    db_host = os.getenv('DB_HOST')
    db_port = os.getenv('DB_PORT')

    try:
        # Connect to the PostgreSQL database using credentials from environment variables
        connection = psycopg2.connect(
            dbname=db_name,
            user=db_user,
            password=db_password,
            host=db_host,
            port=db_port
        )
        
        cursor = connection.cursor()
        
        # Execute query to check if user is a moderator
        query = "SELECT role FROM users WHERE id = %s;"
        cursor.execute(query, (user_id,))
        
        # Fetch result
        result = cursor.fetchone()
        
        # Check if the user has the 'moderator' role
        return result and result[0].lower() == 'moderator'
    
    except Exception as e:
        print(f"An error occurred: {e}")
        return False
    
    finally:
        # Close database connection
        if connection:
            cursor.close()
            connection.close()

# Example usage
user_id = 1
print(is_user_moderator(user_id))