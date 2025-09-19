import os
import psycopg2

def is_user_moderator(user_id):
    # Retrieve connection details from environment variables
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
        query = "SELECT 1 FROM users WHERE id = %s AND is_moderator = TRUE;"
        cursor.execute(query, (user_id,))

        # Fetch result
        result = cursor.fetchone()
        
        return result is not None

    except Exception as e:
        print(f"An error occurred: {e}")
        return False

    finally:
        if connection:
            cursor.close()
            connection.close()

# Example usage
if __name__ == "__main__":
    user_id_to_check = 1  # Replace with the actual user ID you want to check
    is_moderator = is_user_moderator(user_id_to_check)
    print(is_moderator)