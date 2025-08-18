import psycopg2

# Replace these with your actual database credentials
db_host = "your_db_host"
db_name = "your_db_name"
db_user = "your_db_user"
db_password = "your_db_password"

user_id = 1  # Replace this with the user ID you want to check

def is_moderator(user_id):
    conn = None
    try:
        conn = psycopg2.connect(
            host=db_host,
            database=db_name,
            user=db_user,
            password=db_password
        )
        cursor = conn.cursor()
        
        query = """
        SELECT is_moderator FROM users WHERE id = %s;
        """
        cursor.execute(query, (user_id,))
        
        result = cursor.fetchone()
        if result and result[0]:
            return True
        else:
            return False
        
    except Exception as e:
        print(f"An error occurred: {e}")
        return False
    finally:
        if conn is not None:
            conn.close()

# Example usage
print(is_moderator(user_id))