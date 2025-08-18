import sqlite3

def connect_to_database():
    return sqlite3.connect('subscribers.db')

def unsubscribe(email):
    conn = connect_to_database()
    cursor = conn.cursor()
    
    # Check if email exists in the database
    cursor.execute("SELECT * FROM subscribers WHERE email=?", (email,))
    if cursor.fetchone():
        # Remove email from the database
        cursor.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print("You have been successfully unsubscribed.")
    else:
        print("Email not found in our records. Please check your email address.")
    
    conn.close()

if __name__ == "__main__":
    user_email = input("Enter your email address to unsubscribe: ")
    unsubscribe(user_email)