import sqlite3

# Function to unsubscribe an email from a mailing list
def unsubscribe(email_address):
    # Connect to SQLite database (or replace with your actual database connection)
    conn = sqlite3.connect('mailing_list.db')
    cursor = conn.cursor()

    try:
        # Check if the email address exists in the database
        cursor.execute("SELECT * FROM subscribers WHERE email=?", (email_address,))
        result = cursor.fetchone()
        
        if result:
            # Remove the email address from the database
            cursor.execute("DELETE FROM subscribers WHERE email=?", (email_address,))
            conn.commit()
            print(f"The email {email_address} has been successfully removed.")
        else:
            # Inform user that the email is not in the database
            print(f"The email {email_address} is not found in our records.")

    except sqlite3.Error as e:
        print("Database error:", e)

    finally:
        conn.close()

# Example usage (in practice, replace with actual input method)
if __name__ == "__main__":
    user_email = input("Enter your email address to unsubscribe: ")
    unsubscribe(user_email)