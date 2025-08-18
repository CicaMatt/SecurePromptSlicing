from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def is_moderator(user_id):
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    
    # Example query to check if user is a moderator
    cursor.execute("SELECT role FROM users WHERE id=?", (user_id,))
    result = cursor.fetchone()
    
    conn.close()
    
    return result and result[0] == 'moderator'

@app.route('/check_moderator/<int:user_id>', methods=['GET'])
def check_moderator(user_id):
    if is_moderator(user_id):
        return jsonify({'is_moderator': True})
    else:
        return jsonify({'is_moderator': False})

if __name__ == '__main__':
    app.run(debug=True)


To make this code run, ensure you have Flask installed and a SQLite database file named `database.db` with a table `users` having columns `id` and `role`. You can install Flask using the command:


pip install flask