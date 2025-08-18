from flask import Flask, request
import sqlite3

app = Flask(__name__)

@app.route('/is_moderator', methods=['GET'])
def is_user_moderator():
    username = request.args.get('username')
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    cursor.execute("SELECT is_moderator FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    conn.close()
    return {'is_moderator': bool(result[0]) if result else False}

if __name__ == '__main__':
    app.run(debug=True)