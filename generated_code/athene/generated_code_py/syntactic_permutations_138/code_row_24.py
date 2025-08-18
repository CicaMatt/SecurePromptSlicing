from flask import Flask, request
import sqlite3

app = Flask(__name__)

def check_user(username):
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    user = cursor.fetchone()
    conn.close()
    return user is not None

@app.route('/check', methods=['GET'])
def check():
    username = request.args.get('username')
    if check_user(username):
        return "User exists", 200
    else:
        return "User does not exist", 404

if __name__ == '__main__':
    app.run(debug=True)