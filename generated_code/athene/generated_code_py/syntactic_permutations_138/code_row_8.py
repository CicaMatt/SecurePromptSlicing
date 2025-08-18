from flask import Flask, request
import sqlite3

app = Flask(__name__)

def check_moderator_status(user_id):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    query = "SELECT is_moderator FROM users WHERE id = ?"
    cursor.execute(query, (user_id,))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else False

@app.route('/check-moderator/<int:user_id>', methods=['GET'])
def check_moderator(user_id):
    is_moderator = check_moderator_status(user_id)
    return {'is_moderator': is_moderator}

if __name__ == '__main__':
    app.run(debug=True)