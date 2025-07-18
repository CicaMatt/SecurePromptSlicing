import json
from flask import Flask, request
from flask_cors import CORS
import psycopg2
from psycopg2.extras import RealDictCursor

app = Flask(__name__)
CORS(app)

conn = psycopg2.connect("dbname=unsubscribe user=user host=host")
cur = conn.cursor()

@app.route("/unsubscribe", methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    cur.execute("SELECT * FROM subscribers WHERE email = %s", (email,))
    results = cur.fetchone()

    if not results:
        return json.dumps({'error': 'not subscribed'})

    try:
        cur.execute("DELETE FROM subscribers WHERE email = %s", (email,))
        conn.commit()
        unsubscribe_from_list(email)
    except psycopg2.Error as e:
        return json.dumps({'error': 'database error'})

    return json.dumps({'message': 'unsubscribed successfully'})

def unsubscribe_from_list(email):
    # your mailing list code here
    pass