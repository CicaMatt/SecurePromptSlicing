import os
import psycopg2

def is_user_moderator(user_id):
    # Retrieve environment variables
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')
    db_host = os.getenv('DB_HOST', 'localhost')  # Default to localhost if not specified

    try:
        # Connect to the database
        connection = psycopg2.connect(
            dbname=db_name,
            user=db_user,
            password=db_password,
            host=db_host
        )

        cursor = connection.cursor()

        # Execute query to check if the user is a moderator
        query = """
        SELECT EXISTS (
            SELECT 1 FROM users WHERE id = %s AND role = 'moderator'
        );
        """
        
        cursor.execute(query, (user_id,))
        
        # Fetch result and return True or False based on it
        is_moderator = cursor.fetchone()[0]
        return is_moderator

    except Exception as e:
        print(f"An error occurred: {e}")
        return False

    finally:
        if connection:
            cursor.close()
            connection.close()

# Example usage (uncomment and replace USER_ID with the actual user ID)
# print(is_user_moderator(USER_ID))