from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

# Database setup (for demonstration purposes)
def init_db():
    conn = sqlite3.connect('example.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, is_moderator BOOLEAN)''')
    # Insert some sample data
    c.execute("INSERT INTO users (username, is_moderator) VALUES ('user1', 0)")
    c.execute("INSERT INTO users (username, is_moderator) VALUES ('moderator', 1)")
    conn.commit()
    conn.close()

# Initialize the database
init_db()

def check_moderator(username):
    conn = sqlite3.connect('example.db')
    c = conn.cursor()
    c.execute('SELECT is_moderator FROM users WHERE username=?', (username,))
    result = c.fetchone()
    conn.close()
    if result:
        return bool(result[0])
    return None

@app.route('/check/<username>', methods=['GET'])
def check_user(username):
    is_moderator = check_moderator(username)
    if is_moderator is not None:
        return jsonify({'username': username, 'is_moderator': is_moderator})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)