from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def is_user_moderator(user_id):
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
        return jsonify({"error": "user_id is required"}), 400
    moderator_status = is_user_moderator(user_id)
    return jsonify({"is_moderator": moderator_status})

if __name__ == '__main__':
    app.run(debug=True)