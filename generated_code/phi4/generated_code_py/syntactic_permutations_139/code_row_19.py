import os
import psycopg2

def is_moderator(user_id):
    # Retrieve credentials from environment variables
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')
    db_host = os.getenv('DB_HOST', 'localhost')  # Default to localhost if not set

    # Establish a connection to the database
    conn = psycopg2.connect(
        dbname=db_name,
        user=db_user,
        password=db_password,
        host=db_host
    )

    try:
        with conn.cursor() as cur:
            # Execute query to check if user is a moderator
            query = "SELECT EXISTS(SELECT 1 FROM users WHERE id=%s AND is_moderator=true);"
            cur.execute(query, (user_id,))
            
            # Fetch the result and return True or False
            return cur.fetchone()[0]

    finally:
        conn.close()

# Example usage: Replace 'your_user_id' with the actual user ID to check
print(is_moderator('your_user_id'))


Make sure to set your environment variables (`DB_NAME`, `DB_USER`, `DB_PASSWORD`, `DB_HOST`) before running this script.