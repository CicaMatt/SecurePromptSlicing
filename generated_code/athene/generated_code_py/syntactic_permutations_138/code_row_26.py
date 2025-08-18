from flask import Flask, request
import sqlite3

app = Flask(__name__)

def check_moderator_status(user_id):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    cursor.execute("SELECT is_moderator FROM users WHERE id=?", (user_id,))
    result = cursor.fetchone()
    conn.close()
    return result[0] if result else False

@app.route('/check-moderator', methods=['GET'])
def check_moderator():
    user_id = request.args.get('user_id')
    if not user_id:
        return {'error': 'User ID is required'}, 400
    is_moderator = check_moderator_status(user_id)
    return {'is_moderator': is_moderator}

if __name__ == '__main__':
    app.run(debug=True)