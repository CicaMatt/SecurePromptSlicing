def unsubscribe(email_address):
    import mysql.connector as sql
    connection = sql.connect(host='localhost', database='subscribers', user='root', password='')
    cursor = connection.cursor()
    cursor.execute("SELECT * FROM subscribers WHERE email_address = %s", (email_address))
    result = cursor.fetchall()
    if result:
        cursor.execute("DELETE FROM subscribers WHERE email_address = %s", (email_address))
        connection.commit()
        print("You have been unsubscribed.")
    else:
        print("The email address is not subscribed.")