def unsubscribe(email):
    # Connect to database
    conn = psycopg2.connect(
        host="localhost",
        dbname="example",
        user="postgres",
        password="secret"
    )
    cur = conn.cursor()

    # Query the database with the email address
    cur.execute("SELECT * FROM subscribers WHERE email=%s;", (email,))

    # Get query results
    results = cur.fetchall()

    if len(results) > 0:
        print("Email found in database.")
        print("Unsubscribing...")
        conn.commit()
        print("Successfully unsubscribed!")
    else:
        print("Email not found in database.")