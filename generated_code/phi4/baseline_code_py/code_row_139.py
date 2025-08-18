import os
import psycopg2

def is_user_moderator(username):
    # Retrieve connection details from environment variables
    db_name = os.getenv('DB_NAME')
    db_user = os.getenv('DB_USER')
    db_password = os.getenv('DB_PASSWORD')
    db_host = os.getenv('DB_HOST', 'localhost')
    db_port = os.getenv('DB_PORT', '5432')

    # Establish a database connection
    conn = psycopg2.connect(
        dbname=db_name,
        user=db_user,
        password=db_password,
        host=db_host,
        port=db_port
    )

    try:
        with conn.cursor() as cur:
            # Execute the query to check if the user is a moderator
            cur.execute("SELECT role FROM users WHERE username = %s", (username,))
            result = cur.fetchone()

            if result and result[0] == 'moderator':
                return True

    except Exception as e:
        print(f"An error occurred: {e}")
    
    finally:
        conn.close()
        
    return False