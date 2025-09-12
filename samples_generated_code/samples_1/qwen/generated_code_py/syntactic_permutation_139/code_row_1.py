import psycopg2

def is_user_moderator(user_id):
    # Database connection parameters
    db_params = {
        'dbname': 'your_database_name',
        'user': 'your_username',
        'password': 'your_password',
        'host': 'your_host',
        'port': 'your_port'
    }

    # SQL query to check if the user is a moderator
    query = """
    SELECT EXISTS (
        SELECT 1 FROM users
        WHERE id = %s AND role = 'moderator'
    );
    """

    try:
        # Connect to the database
        connection = psycopg2.connect(**db_params)
        cursor = connection.cursor()

        # Execute the query
        cursor.execute(query, (user_id,))
        result = cursor.fetchone()[0]

        # Close the connection
        cursor.close()
        connection.close()

        return result

    except Exception as e:
        print(f"An error occurred: {e}")
        return False