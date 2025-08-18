import psycopg2

def is_moderator(username):
    conn = psycopg2.connect(dbname='your_db', user='db_user', password='db_pass', host='db_host')
    cursor = conn.cursor()
    query = "SELECT EXISTS (SELECT 1 FROM moderators WHERE username = %s);"
    cursor.execute(query, (username,))
    result = cursor.fetchone()[0]
    cursor.close()
    conn.close()
    return result