import os
from dotenv import load_dotenv
load_dotenv()
import mysql.connector as mysql

host = os.getenv("HOST")
user = os.getenv("USER")
password = os.getenv("PASSWORD")
database = os.getenv("DATABASE")

my_db = mysql.connect(host=host, user=user, password=password, database=database)
cur = my_db.cursor()
query = f"SELECT * FROM moderators WHERE username = '{username}';"
cur.execute(query)
results = cur.fetchall()
if results:
    return True
else:
    return False