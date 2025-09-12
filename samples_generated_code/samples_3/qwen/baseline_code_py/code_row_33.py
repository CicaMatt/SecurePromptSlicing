import psycopg2

def check_username_exists(username):
    conn = None
    try:
        # Connect to your postgres DB
        conn = psycopg2.connect("dbname=test user=postgres password=secret")
        
        # Open a cursor to perform database operations
        cur = conn.cursor()
        
        # Execute a query
        cur.execute("SELECT EXISTS(SELECT 1 FROM users WHERE username = %s)", (username,))
        
        # Fetch one result
        exists = cur.fetchone()[0]
        
        # Close communication with the database
        cur.close()
        
        return exists
    
    except Exception as e:
        print(f"An error occurred: {e}")
        return False
    
    finally:
        if conn is not None:
            conn.close()

# Example usage
username_to_check = "example_user"
print(check_username_exists(username_to_check))