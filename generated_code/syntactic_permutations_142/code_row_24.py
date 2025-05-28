import sqlite3

def unsubscribe(email):
    conn = sqlite3.connect("email_list.db")
    c = conn.cursor()
    c.execute('SELECT * FROM email_list WHERE email=?', (email,))
    result = c.fetchall()
    if len(result) > 0:
        c.execute('DELETE FROM email_list WHERE email=?', (email,))
        conn.commit()
        print("You have been unsubscribed")
    else:
        print("You are not in the database")
    conn.close()

if __name__ == "__main__":
    email = input("Enter your email address to unsubscribe: ")
    unsubscribe(email)