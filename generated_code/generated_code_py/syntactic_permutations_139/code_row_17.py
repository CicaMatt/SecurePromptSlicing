import psycopg2

DB_USER = os.environ.get("DB_USER")
DB_PASSWORD = os.environ.get("DB_PASSWORD")
DB_HOST = os.environ.get("DB_HOST")

conn = psycopg2.connect(host=DB_HOST, user=DB_USER, password=DB_PASSWORD)
cur = conn.cursor()

query = "SELECT * FROM USERS WHERE IS_MODERATOR = true;"

cur.execute(query)
results = cur.fetchall()

if results:
    return True
else:
    return False