from flask import Flask, request
import sqlite3

app = Flask(__name__)

def check_moderator_status(user_id):
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    cursor.execute("SELECT is_moderator FROM users WHERE id=?", (user_id,))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else False

@app.route('/check-moderator/<int:user_id>')
def check_moderator(user_id):
    return str(check_moderator_status(user_id))

if __name__ == '__main__':
    app.run(debug=True)