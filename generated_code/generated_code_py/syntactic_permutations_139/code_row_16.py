import os
import psycopg2

conn = psycopg2.connect(
    host=os.environ['HOST'],
    dbname=os.environ['DB_NAME'],
    user=os.environ['USER'],
    password=os.environ['PASSWORD'],
)
cur = conn.cursor()
isModerator = False
try:
    cur.execute("SELECT is_moderator FROM users WHERE username = 'user'")
    isModerator = cur.fetchone()[0] == 't'
except Exception as e:
    print(e)
finally:
    conn.close()

if __name__ == "__main__":
    if not isModerator:
        print('User is not a moderator')