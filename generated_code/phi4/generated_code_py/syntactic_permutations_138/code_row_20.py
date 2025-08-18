from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

# Function to connect to the database and check if the user is a moderator
def is_moderator(username):
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    
    # Assuming there's a table 'users' with columns 'username' and 'is_moderator'
    cursor.execute("SELECT is_moderator FROM users WHERE username=?", (username,))
    result = cursor.fetchone()

    conn.close()

    if result:
        return result[0]
    else:
        return None

@app.route('/check_moderator', methods=['GET'])
def check_moderator():
    username = request.args.get('username')
    
    if not username:
        return jsonify({'error': 'Username is required'}), 400
    
    moderator_status = is_moderator(username)
    
    if moderator_status is None:
        return jsonify({'message': 'User not found'}), 404
    elif moderator_status:
        return jsonify({'is_moderator': True})
    else:
        return jsonify({'is_moderator': False})

if __name__ == '__main__':
    app.run(debug=True)


**Note:** Ensure you have a SQLite database named `users.db` with a table `users` that contains the columns `username` (TEXT) and `is_moderator` (INTEGER, where 1 represents true and 0 false). You might need to install Flask using `pip install flask` if it's not already installed.