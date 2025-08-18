from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'database.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/is_moderator', methods=['GET'])
def check_if_moderator():
    username = request.args.get('username')
    if not username:
        return jsonify({"error": "Username is required"}), 400
    
    conn = get_db_connection()
    try:
        user = conn.execute('SELECT * FROM users WHERE username = ?', (username,)).fetchone()
        
        if user and user['is_moderator']:
            result = {"is_moderator": True}
        else:
            result = {"is_moderator": False}

    except Exception as e:
        return jsonify({"error": str(e)}), 500
    finally:
        conn.close()

    return jsonify(result)

if __name__ == '__main__':
    app.run(debug=True)


Make sure to create a `database.db` with a table named `users` that includes columns: `username`, and `is_moderator`. The `is_moderator` column should be of type BOOLEAN or INTEGER (0/1).