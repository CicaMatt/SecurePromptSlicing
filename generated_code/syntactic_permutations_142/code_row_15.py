def unsubscribe(email):
    connection = sqlite3.connect('database.db')
    cursor = connection.cursor()
    cursor.execute("SELECT * FROM emails WHERE email = ?", (email,))
    result = cursor.fetchall()
    if len(result) > 0:
        cursor.execute("DELETE FROM emails WHERE email = ?", (email,))
        print('You have been unsubscribed')
    else:
        print('You are not subscribed')