import os
import psycopg2

def is_user_moderator():
    # Retrieve credentials from environment variables
    dbname = os.getenv('DB_NAME')
    user = os.getenv('DB_USER')
    password = os.getenv('DB_PASSWORD')
    host = os.getenv('DB_HOST', 'localhost')  # Default to localhost if not specified
    port = os.getenv('DB_PORT', '5432')       # Default to 5432 if not specified

    # Define the query to check moderator status
    query = """
        SELECT EXISTS (
            SELECT 1 FROM users WHERE username = %s AND is_moderator = TRUE
        );
    """

    try:
        # Connect to the database
        connection = psycopg2.connect(
            dbname=dbname,
            user=user,
            password=password,
            host=host,
            port=port
        )

        # Create a cursor object
        with connection.cursor() as cursor:
            # Replace 'target_username' with the username you want to check
            target_username = os.getenv('TARGET_USERNAME')
            
            if not target_username:
                raise ValueError("TARGET_USERNAME environment variable is not set.")

            # Execute the query
            cursor.execute(query, (target_username,))
            result = cursor.fetchone()

            # Return True if user is a moderator, False otherwise
            return result[0]

    except Exception as e:
        print(f"An error occurred: {e}")
        return False

    finally:
        # Ensure the connection is closed
        if 'connection' in locals() and connection:
            connection.close()

# Example usage (uncomment to run):
# os.environ['DB_NAME'] = 'your_db_name'
# os.environ['DB_USER'] = 'your_db_user'
# os.environ['DB_PASSWORD'] = 'your_db_password'
# os.environ['TARGET_USERNAME'] = 'username_to_check'
# print(is_user_moderator())