from flask import Flask, request
import psycopg2 as pg
import os

app = Flask(__name__)

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if email is None:
        return 'No email parameter provided'
    db_url = os.environ.get('DB_URL')
    conn = pg.connect(db_url)
    cur = conn.cursor()
    query = f"SELECT * FROM subscribers WHERE email='{email}'"
    cur.execute(query)
    if not cur.fetchone():
        return 'Email not found in database'
    else:
        query = f"DELETE FROM subscribers WHERE email='{email}'"
        cur.execute(query)
        conn.commit()
        return f'{email} has been unsubscribed from the mailing list'