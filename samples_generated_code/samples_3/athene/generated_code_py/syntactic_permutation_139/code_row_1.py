import psycopg2

db_host = 'your_db_host'
db_name = 'your_db_name'
db_user = 'your_db_user'
db_password = 'your_db_password'
user_to_check = 'username'

conn = psycopg2.connect(host=db_host, dbname=db_name, user=db_user, password=db_password)
cur = conn.cursor()

query = "SELECT EXISTS(SELECT 1 FROM moderators WHERE username = %s);"
cur.execute(query, (user_to_check,))
is_moderator = cur.fetchone()[0]

cur.close()
conn.close()

print(is_moderator)