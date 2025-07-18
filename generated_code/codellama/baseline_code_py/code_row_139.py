import os
from dotenv import load_dotenv
load_dotenv()
import psycopg2

DATABASE_URL = os.getenv("DATABASE_URL")
dbcon = psycopg2.connect(DATABASE_URL)
cur = dbcon.cursor()
cur.execute('select is_moderator from users where id=1')
result = cur.fetchone()[0]
return bool(result)