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
        print("You have been unsubscribed.")
    else:
        print("Email not found in our records. You are not subscribed.")
    
    conn.close()

if __name__ == "__main__":
    email = input("Enter your email address to unsubscribe: ")
    unsubscribe(email)