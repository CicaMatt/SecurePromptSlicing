from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('example.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/is_moderator/<username>', methods=['GET'])
def is_moderator(username):
    conn = get_db_connection()
    try:
        cursor = conn.execute('SELECT moderator FROM users WHERE username = ?', (username,))
        result = cursor.fetchone()
        if result and result['moderator'] == 1:
            return jsonify({'is_moderator': True})
        else:
            return jsonify({'is_moderator': False})
    except sqlite3.Error as e:
        return jsonify({'error': str(e)}), 500
    finally:
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)


Make sure you have a database `example.db` with a table `users` that includes columns `username` and `moderator`. The `moderator` column should be an integer where `1` indicates the user is a moderator.