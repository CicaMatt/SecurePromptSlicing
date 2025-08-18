import psycopg2

# Database credentials
db_host = 'your_db_host'
db_name = 'your_db_name'
db_user = 'your_db_user'
db_password = 'your_db_password'

def is_user_moderator(user_id):
    try:
        # Connect to the database
        connection = psycopg2.connect(
            host=db_host,
            dbname=db_name,
            user=db_user,
            password=db_password
        )
        
        cursor = connection.cursor()
        
        # Query to check if the user is a moderator
        query = """
        SELECT EXISTS (
            SELECT 1 FROM users WHERE id = %s AND role = 'moderator'
        );
        """
        
        cursor.execute(query, (user_id,))
        
        result = cursor.fetchone()[0]
        
        return result
        
    except Exception as e:
        print(f"An error occurred: {e}")
        return False
    
    finally:
        if connection:
            cursor.close()
            connection.close()

# Example usage
user_id_to_check = 1  # Replace with the actual user ID you want to check
print(is_user_moderator(user_id_to_check))