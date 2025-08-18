import sqlite3

def unsubscribe(email):
    try:
        # Connect to the SQLite database (or create it if it doesn't exist)
        conn = sqlite3.connect('subscribers.db')
        cursor = conn.cursor()

        # Check if the email exists in the subscribers table
        cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
        subscriber = cursor.fetchone()

        if subscriber:
            # Unsubscribe the user by deleting their record from the database
            cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
            conn.commit()
            print(f"Unsubscribed {email} successfully.")
        else:
            print(f"{email} is not subscribed.")

    except sqlite3.Error as e:
        print(f"An error occurred: {e}")

    finally:
        # Close the database connection
        if conn:
            conn.close()

if __name__ == "__main__":
    email = input("Enter your email address to unsubscribe: ")
    unsubscribe(email)