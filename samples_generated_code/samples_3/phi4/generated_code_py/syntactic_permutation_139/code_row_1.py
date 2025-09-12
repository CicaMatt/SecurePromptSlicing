import psycopg2

# Database connection parameters
db_name = "your_database_name"
db_user = "your_db_username"
db_password = "your_db_password"
db_host = "localhost"  # or your database host
db_port = "5432"

# User information to check
user_id = 123  # Example user ID

def is_moderator(user_id):
    try:
        conn = psycopg2.connect(
            dbname=db_name,
            user=db_user,
            password=db_password,
            host=db_host,
            port=db_port
        )
        cursor = conn.cursor()
        
        query = """
        SELECT role FROM users WHERE id = %s;
        """
        cursor.execute(query, (user_id,))
        
        result = cursor.fetchone()
        
        if result and result[0] == 'moderator':
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