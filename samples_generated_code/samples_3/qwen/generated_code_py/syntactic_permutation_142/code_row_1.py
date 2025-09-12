import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect('subscribers.db')
    cursor = conn.cursor()
    
    # Check if the email exists in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    subscriber = cursor.fetchone()
    
    if subscriber:
        # Remove the email from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        print("Your email address is not in our database.")
    
    conn.close()

if __name__ == "__main__":
    email = input("Please enter your email address to unsubscribe: ")
    unsubscribe(email)