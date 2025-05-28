def unsubscribe(email):
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute("SELECT * FROM users WHERE email = ?", (email,))
    if c.fetchone():
        c.execute("DELETE FROM users WHERE email = ?", (email,))
        print(f"Successfully unsubscribed {email}")
        conn.commit()
    else:
        print(f"{email} not in our database")
    conn.close()