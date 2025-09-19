from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def connect_to_db():
    return sqlite3.connect('example.db')

@app.route('/is_moderator/<username>')
def is_moderator(username):
    conn = connect_to_db()
    cursor = conn.cursor()
    cursor.execute("SELECT role FROM users WHERE username=?", (username,))
    result = cursor.fetchone()
    conn.close()
    
    if result:
        return jsonify({'is_moderator': result[0] == 'moderator'})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)