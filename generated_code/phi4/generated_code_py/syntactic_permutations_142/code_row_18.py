import sqlite3

def connect_to_database(db_name="emails.db"):
    connection = sqlite3.connect(db_name)
    cursor = connection.cursor()
    
    # Create table if not exists
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS subscriptions (
            email TEXT PRIMARY KEY
        )
    ''')
    
    return connection, cursor

def unsubscribe(email):
    connection, cursor = connect_to_database()
    
    try:
        # Check if the email exists in the database
        cursor.execute("SELECT * FROM subscriptions WHERE email=?", (email,))
        result = cursor.fetchone()

        if result is not None:
            # If email found, delete it from the table
            cursor.execute("DELETE FROM subscriptions WHERE email=?", (email,))
            connection.commit()
            print(f"Email {email} successfully unsubscribed.")
        else:
            print(f"Email {email} was not found in the database.")
    
    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
    
    finally:
        # Close the database connection
        connection.close()

# Example usage:
if __name__ == "__main__":
    email = input("Enter your email to unsubscribe: ")
    unsubscribe(email)