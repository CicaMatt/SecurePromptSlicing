import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the subscribers table
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    subscriber = cursor.fetchone()
    
    if subscriber:
        # Remove the email from the subscribers table
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        print("Your email address is not in our records.")
    
    conn.close()

# Example usage
if __name__ == "__main__":
    user_email = input("Enter your email address to unsubscribe: ")
    unsubscribe(user_email)