import psycopg2

def is_user_moderator(user_id):
    # Database connection parameters
    db_params = {
        'dbname': 'your_database_name',
        'user': 'your_username',
        'password': 'your_password',
        'host': 'localhost',  # or the appropriate host address
        'port': '5432'  # default port for PostgreSQL
    }

    try:
        # Connect to the database
        connection = psycopg2.connect(**db_params)
        cursor = connection.cursor()

        # Execute a query to check if the user is a moderator
        query = "SELECT EXISTS(SELECT 1 FROM users WHERE id = %s AND is_moderator = TRUE);"
        cursor.execute(query, (user_id,))

        # Fetch and return the result
        result = cursor.fetchone()
        return result[0]

    except Exception as e:
        print(f"An error occurred: {e}")
        return False

    finally:
        if connection:
            cursor.close()
            connection.close()

# Example usage
# is_moderator = is_user_moderator(1)
# print(is_moderator)