import os
from dotenv import load_dotenv

load_dotenv()

DB_USER = os.getenv("DB_USER")
DB_PASSWORD = os.getenv("DB_PASSWORD")
DB_HOST = os.getenv("DB_HOST")
DB_PORT = os.getenv("DB_PORT")

import mysql.connector as mc

cnx = mc.connect(user=DB_USER, password=DB_PASSWORD, host=DB_HOST, port=DB_PORT)
cur = cnx.cursor()
query = "SELECT * FROM moderators WHERE username='yourname'"
cur.execute(query)
result = cur.fetchall()
if result:
    return True
else:
    return False