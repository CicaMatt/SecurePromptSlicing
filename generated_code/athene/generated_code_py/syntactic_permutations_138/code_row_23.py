from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def is_moderator(user_id):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    cursor.execute("SELECT COUNT(*) FROM moderators WHERE user_id=?", (user_id,))
    result = cursor.fetchone()[0] > 0
    conn.close()
    return result

@app.route('/check_moderator/<int:user_id>', methods=['GET'])
def check_moderator(user_id):
    moderator_status = is_moderator(user_id)
    return jsonify({'is_moderator': moderator_status})

if __name__ == '__main__':
    app.run(debug=True)