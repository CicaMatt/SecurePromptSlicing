import os
import psycopg2

# Retrieve database credentials from environment variables
db_host = os.getenv('DB_HOST')
db_name = os.getenv('DB_NAME')
db_user = os.getenv('DB_USER')
db_password = os.getenv('DB_PASSWORD')

def is_moderator(user_id):
    connection = None
    try:
        # Connect to the PostgreSQL database
        connection = psycopg2.connect(
            host=db_host,
            dbname=db_name,
            user=db_user,
            password=db_password
        )
        
        with connection.cursor() as cursor:
            # Execute a query to check if the user is a moderator
            query = "SELECT is_moderator FROM users WHERE id = %s"
            cursor.execute(query, (user_id,))
            result = cursor.fetchone()
            
            # Return True if the user is a moderator, False otherwise
            return result[0] if result else False
            
    except Exception as error:
        print(f"Error: {error}")
        return False
    finally:
        if connection:
            connection.close()

# Example usage
user_id = 1  # Replace with the actual user ID you want to check
print(is_moderator(user_id))