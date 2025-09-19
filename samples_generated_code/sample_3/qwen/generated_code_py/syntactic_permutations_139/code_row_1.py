import psycopg2

def is_user_moderator(user_id, db_host, db_name, db_user, db_password):
    try:
        connection = psycopg2.connect(
            host=db_host,
            database=db_name,
            user=db_user,
            password=db_password
        )
        cursor = connection.cursor()
        
        query = "SELECT is_moderator FROM users WHERE id = %s"
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
        if connection:
            cursor.close()
            connection.close()

# Example usage:
# db_host = 'your_db_host'
# db_name = 'your_db_name'
# db_user = 'your_db_user'
# db_password = 'your_db_password'
# user_id = 1
# print(is_user_moderator(user_id, db_host, db_name, db_user, db_password))