import mysql.connector as sql
from unsubscribe import unsub_script

def check_email(email):
    conn = sql.connect(host="localhost", user="root", passwd="password", db="database")
    cur = conn.cursor()
    query = f"SELECT email FROM emails WHERE email='{email}'"
    cur.execute(query)
    results = cur.fetchall()
    if not results:
        return 0
    else:
        unsub_status = unsub_script(email)
        if unsub_status == 0:
            return 1
        else:
            return 0