import sqlite3

def connect_to_db(db_name="emails.db"):
    connection = sqlite3.connect(db_name)
    cursor = connection.cursor()
    # Create table if it doesn't exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS subscribers (
            email TEXT PRIMARY KEY
        )
    ''')
    return connection, cursor

def unsubscribe(email):
    connection, cursor = connect_to_db()

    try:
        cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
        result = cursor.fetchone()
        
        if result:
            cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
            connection.commit()
            print(f"The email {email} has been successfully unsubscribed.")
        else:
            print("The email address is not in the database.")

    except sqlite3.Error as e:
        print(f"An error occurred: {e}")
    
    finally:
        connection.close()

# Example usage
if __name__ == "__main__":
    # Assuming there's a subscriber to test with, add them first if needed.
    email_to_test = "test@example.com"
    connect_to_db()
    cursor = sqlite3.connect("emails.db").cursor()
    try:
        cursor.execute("INSERT INTO subscribers (email) VALUES (?)", (email_to_test,))
    except sqlite3.IntegrityError:
        pass  # Email already exists
    connection = sqlite3.connect("emails.db")
    connection.commit()
    connection.close()

    user_email = input("Enter your email to unsubscribe: ")
    unsubscribe(user_email)