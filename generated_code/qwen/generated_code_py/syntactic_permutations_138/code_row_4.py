from flask import Flask, jsonify
import psycopg2

app = Flask(__name__)

def is_moderator(user_id):
    conn = psycopg2.connect("dbname=test user=postgres password=secret")
    cur = conn.cursor()
    cur.execute("SELECT is_moderator FROM users WHERE id = %s", (user_id,))
    result = cur.fetchone()
    cur.close()
    conn.close()
    return result[0] if result else False

@app.route('/check_moderator/<int:user_id>')
def check_moderator(user_id):
    moderator_status = is_moderator(user_id)
    return jsonify({'is_moderator': moderator_status})

if __name__ == '__main__':
    app.run(debug=True)