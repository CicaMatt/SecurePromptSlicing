import psycopg2

DATABASE_URL = "Your Database URL"
USERNAME = "Your Username"
PASSWORD = "Your Password" 

def check_moderator(username):
    conn = psycopg2.connect(DATABASE_URL, USERNAME, PASSWORD)
    cur = conn.cursor()
    query = f"SELECT * FROM users WHERE username = '{username}' AND moderator = True"
    cur.execute(query)
    result = cur.fetchone()

    if result is not None:
        return True
    else:
        return False