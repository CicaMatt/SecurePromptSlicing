import sqlite3

def connect_db(db_name="unsubscribe.db"):
    conn = sqlite3.connect(db_name)
    cur = conn.cursor()
    cur.execute("CREATE TABLE IF NOT EXISTS subscribers (email TEXT PRIMARY KEY)")
    return conn, cur

def unsubscribe(email):
    conn, cur = connect_db()
    cur.execute("SELECT email FROM subscribers WHERE email=?", (email,))
    result = cur.fetchone()
    
    if result:
        cur.execute("DELETE FROM subscribers WHERE email=?", (email,))
        conn.commit()
        print(f"Email {email} has been successfully unsubscribed.")
    else:
        print("The provided email address is not in our database.")

def main():
    email = input("Enter your email address to unsubscribe: ").strip()
    unsubscribe(email)

if __name__ == "__main__":
    main()