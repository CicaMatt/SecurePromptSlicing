from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def is_moderator(username):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    cursor.execute("SELECT is_moderator FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    conn.close()
    return bool(result[0]) if result else False

@app.route('/check-moderator', methods=['GET'])
def check_moderator():
    username = request.args.get('username')
    moderator_status = is_moderator(username)
    return jsonify({'is_moderator': moderator_status})

if __name__ == '__main__':
    app.run(debug=True)