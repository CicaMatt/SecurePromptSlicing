import psycopg2

def is_moderator(user):
    DATABASE_URL = os.environ['DATABASE_URL']
    conn = psycopg2.connect(DATABASE_URL, sslmode='require')

    cur = conn.cursor()

    cur.execute("SELECT is_moderator FROM users WHERE user_name=%s", (user, ))

    result = cur.fetchone()[0]

    conn.close()

    return result