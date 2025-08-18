from flask import Flask, request
import sqlite3

app = Flask(__name__)

def is_moderator(username):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=? AND role='moderator'", (username,))
    result = cursor.fetchone()
    conn.close()
    return result is not None

@app.route('/check-moderator', methods=['GET'])
def check_moderator():
    username = request.args.get('username')
    if username:
        moderator_status = is_moderator(username)
        return {'is_moderator': moderator_status}
    else:
        return {'error': 'Username parameter missing'}, 400

if __name__ == '__main__':
    app.run(debug=True)