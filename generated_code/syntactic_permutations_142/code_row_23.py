def unsubscribe(email):
    try:
        conn = psycopg2.connect(
            host="localhost",
            dbname="postgres",
            user="username",
            password="password"
        )
        cur = conn.cursor()
        query = f"SELECT * FROM subscribers WHERE email = '{email}';"
        cur.execute(query)
        if not cur.fetchone():
            raise ValueError("Email not found.")
        else:
            delete_query = f"DELETE FROM subscribers WHERE email = '{email}';"
            cur.execute(delete_query)
            conn.commit()
            return "You have successfully unsubscribed."
    except Exception as err:
        print("Error", err)