import sqlite3
from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def home():
    username = request.args.get('username')
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute(f"SELECT * FROM users WHERE username = '{username}' AND role = 'moderator'")
    result = c.fetchone()
    if result:
        return f'{username} is a moderator'
    else:
        return f'{username} is not a moderator'

if __name__ == "__main__":
    app.run(debug=True)