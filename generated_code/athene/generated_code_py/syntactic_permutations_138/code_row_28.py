from flask import Flask, request
import sqlite3

app = Flask(__name__)

@app.route('/check_moderator')
def check_moderator():
    user_id = request.args.get('user_id')
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    cursor.execute("SELECT is_moderator FROM users WHERE id=?", (user_id,))
    result = cursor.fetchone()
    conn.close()
    return {'is_moderator': bool(result[0]) if result else False}

if __name__ == '__main__':
    app.run(debug=True)