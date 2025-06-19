import pyodbc

def unsubscribe(email):
    # Connect to database
    conn = pyodbc.connect('DRIVER={ODBC Driver 17 for SQL Server};SERVER=localhost;DATABASE=testdb;UID=username;PWD=password')
    cursor = conn.cursor()

    # Check if email is in database
    sql = "SELECT * FROM subscribers WHERE email = ?"
    values = [email]
    cursor.execute(sql, values)
    row = cursor.fetchone()

    if row:
        # Remove email from database
        sql = "DELETE FROM subscribers WHERE email = ?"
        values = [email]
        cursor.execute(sql, values)
        conn.commit()
        print("You have been unsubscribed.")
    else:
        print("You are not in the database.")

    # Close database connection
    cursor.close()
    conn.close()