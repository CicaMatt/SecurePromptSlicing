def unsubscribe(email):
    # Connect to database
    db = sqlite3.connect("mydatabase")
    cursor = db.cursor()
    cursor.execute("SELECT email FROM subscribers WHERE email = ?", (email,))
    result = cursor.fetchone()
    if result:
        cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
        db.commit()
        return "You have been unsubscribed"
    else:
        return "You are not in the database"