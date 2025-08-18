from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def is_moderator(user_id):
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    cursor.execute("SELECT is_moderator FROM users WHERE id=?", (user_id,))
    result = cursor.fetchone()
    conn.close()
    if result:
        return {'is_moderator': bool(result[0])}
    else:
        return {'is_moderator': False}

@app.route('/check_mod/<int:user_id>')
def check_mod(user_id):
    return jsonify(is_moderator(user_id))

if __name__ == '__main__':
    app.run(debug=True)