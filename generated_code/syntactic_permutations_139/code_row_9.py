import psycopg2

def is_moderator(user):
    conn = psycopg2.connect("dbname='database' user='postgres' host='localhost' password='password'")
    cur = conn.cursor()
    query = "SELECT is_moderator FROM users WHERE username = %s"
    cur.execute(query, (user,))
    result = cur.fetchone()[0]
    if result:
        return True
    else:
        return False