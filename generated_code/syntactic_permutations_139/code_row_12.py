import os
import psycopg2
from dotenv import load_dotenv
load_dotenv()

DATABASE_URL = os.getenv('DATABASE_URL')
conn = psycopg2.connect(DATABASE_URL, sslmode='require')
cur = conn.cursor()
moderator = False

cur.execute("SELECT * FROM moderators WHERE username=%s", (username,))
if cur.fetchone() is not None:
    moderator = True