from flask import Flask, request
import sqlite3

app = Flask(__name__)

def get_user_from_db(username):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    conn.close()
    return user

@app.route('/check_user', methods=['GET'])
def check_user():
    username = request.args.get('username')
    user = get_user_from_db(username)
    if user:
        return {'exists': True}
    else:
        return {'exists': False}

if __name__ == '__main__':
    app.run(debug=True)