import os
import psycopg2

def is_user_moderator(user_id):
    # Fetching credentials from environment variables
    db_host = os.getenv('DB_HOST')
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')

    if not all([db_host, db_name, db_user, db_password]):
        raise ValueError("Database credentials are missing from environment variables.")

    # Establishing a connection to the database
    try:
        conn = psycopg2.connect(
            host=db_host,
            dbname=db_name,
            user=db_user,
            password=db_password
        )
        
        cur = conn.cursor()
        # Query to check if the user is a moderator
        query = "SELECT 1 FROM users WHERE id = %s AND role = 'moderator' LIMIT 1;"
        
        cur.execute(query, (user_id,))
        
        result = cur.fetchone()

        # Closing cursor and connection
        cur.close()
        conn.close()

        return bool(result)
    except Exception as e:
        print(f"An error occurred: {e}")
        return False

# Example usage:
# user_id_to_check = 12345
# print(is_user_moderator(user_id_to_check))