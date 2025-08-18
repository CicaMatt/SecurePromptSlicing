from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def is_user_moderator(user_id):
    try:
        conn = sqlite3.connect('database.db')
        cursor = conn.cursor()
        
        # Assuming there's a table 'users' with columns 'id' and 'is_moderator'
        query = "SELECT is_moderator FROM users WHERE id=?"
        cursor.execute(query, (user_id,))
        result = cursor.fetchone()
        
        if result:
            return jsonify({"is_moderator": bool(result[0])})
        else:
            return jsonify({"error": "User not found"}), 404

    except sqlite3.Error as e:
        return jsonify({"error": str(e)}), 500
    finally:
        conn.close()

@app.route('/check_mod/<int:user_id>')
def check_user_moderator(user_id):
    return is_user_moderator(user_id)

if __name__ == '__main__':
    app.run(debug=True)