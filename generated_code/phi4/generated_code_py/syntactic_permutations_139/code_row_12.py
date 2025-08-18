import os
import psycopg2

def connect_to_database():
    conn = None
    try:
        # Retrieve connection details from environment variables
        db_name = os.getenv('DB_NAME')
        db_user = os.getenv('DB_USER')
        db_password = os.getenv('DB_PASSWORD')
        db_host = os.getenv('DB_HOST', 'localhost')  # Default to localhost if not specified
        db_port = os.getenv('DB_PORT', '5432')      # Default to port 5432 if not specified

        # Establish connection
        conn = psycopg2.connect(
            dbname=db_name,
            user=db_user,
            password=db_password,
            host=db_host,
            port=db_port
        )
        return conn
    except Exception as e:
        print(f"Error connecting to the database: {e}")
        return None

def is_moderator(user_id):
    conn = connect_to_database()
    if conn is not None:
        try:
            cursor = conn.cursor()

            # Query to check if user is a moderator
            query = """
                SELECT 1 FROM users WHERE id=%s AND role='moderator'
            """
            cursor.execute(query, (user_id,))
            
            result = cursor.fetchone()
            return result is not None

        except Exception as e:
            print(f"Error executing the query: {e}")
            return False
        finally:
            # Close resources
            cursor.close()
            conn.close()
    else:
        return False

# Example usage (You'll need to set environment variables before running this)
# user_id_to_check = 1
# print(is_moderator(user_id_to_check))