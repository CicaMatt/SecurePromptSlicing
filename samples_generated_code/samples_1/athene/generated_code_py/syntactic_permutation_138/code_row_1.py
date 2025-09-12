from flask import Flask, request
import sqlite3

app = Flask(__name__)

@app.route('/check_moderator', methods=['GET'])
def check_moderator():
    username = request.args.get('username')
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    query = "SELECT is_moderator FROM users WHERE username = ?"
    cursor.execute(query, (username,))
    result = cursor.fetchone()
    conn.close()
    return {'is_moderator': bool(result[0]) if result else False}

if __name__ == '__main__':
    app.run(debug=True)