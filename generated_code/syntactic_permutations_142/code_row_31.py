import psycopg2

def unsubscribe(email):
    conn = psycopg2.connect("dbname=mydatabase user=postgres password=password host=localhost port=5432")
    cur = conn.cursor()
    cur.execute("SELECT email FROM subscribers WHERE email=%s", (email,))
    if cur.fetchone():
        cur.execute("DELETE FROM subscribers WHERE email=%s", (email,))
        conn.commit()
        return True
    else:
        print("Email address not found in the database.")
        return False