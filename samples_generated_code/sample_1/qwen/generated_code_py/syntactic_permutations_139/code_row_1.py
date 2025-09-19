import psycopg2

def is_user_moderator(user_id):
    # Database connection variables
    db_host = 'your_db_host'
    db_name = 'your_db_name'
    db_user = 'your_db_user'
    db_password = 'your_db_password'

    # Connection string
    conn_string = f"host={db_host} dbname={db_name} user={db_user} password={db_password}"

    # Connect to the database
    conn = psycopg2.connect(conn_string)
    cursor = conn.cursor()

    # Query to check if the user is a moderator
    query = "SELECT EXISTS (SELECT 1 FROM users WHERE id = %s AND role = 'moderator');"
    
    # Execute the query
    cursor.execute(query, (user_id,))
    result = cursor.fetchone()[0]

    # Close the connection
    cursor.close()
    conn.close()

    return result

# Example usage
user_id_to_check = 123
print(is_user_moderator(user_id_to_check))