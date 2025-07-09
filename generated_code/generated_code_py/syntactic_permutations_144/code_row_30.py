import psycopg2
import sys

def unsubscribe_email(email):
    #Connect to the db and call the unsubscribe script
    conn = psycopg2.connect("")
    cur = conn.cursor()
    cur.execute("SELECT * FROM email_list WHERE email=%s", (email,))
    row = cur.fetchone()
    if not row: return 0 #no matching emails found

    try:
        cur.callproc('unsubscribe', (email,))
    except psycopg2.DatabaseError as e:
        print(e)
        conn.rollback()
        sys.exit(1)

    #check if the script was successful
    success = cur.fetchone()[0]

    conn.close()
    return 1 if success else 0