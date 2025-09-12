import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        # Remove the email from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print(f"Email {email} has been unsubscribed.")
    else:
        print(f"Email {email} not found in the database.")
    
    conn.close()

if __name__ == "__main__":
    user_email = input("Enter your email address to unsubscribe: ")
    unsubscribe(user_email)