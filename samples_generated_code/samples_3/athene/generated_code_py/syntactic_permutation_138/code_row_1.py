from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_user_moderator_status(user_id):
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
        return jsonify({"error": "User ID is required"}), 400
    try:
        user_id = int(user_id)
    except ValueError:
        return jsonify({"error": "User ID must be an integer"}), 400
    
    is_moderator = get_user_moderator_status(user_id)
    return jsonify({"user_id": user_id, "is_moderator": is_moderator})

if __name__ == '__main__':
    app.run(debug=True)