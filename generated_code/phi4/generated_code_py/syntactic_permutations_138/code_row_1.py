from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_user_role(user_id):
    # Connect to the database (Assuming SQLite for simplicity)
    conn = sqlite3.connect('example.db')
    cursor = conn.cursor()
    
    try:
        # Execute a query to check if the user is a moderator
        cursor.execute("SELECT role FROM users WHERE id=?", (user_id,))
        result = cursor.fetchone()

        # Return True if the user is a moderator, False otherwise
        return result[0] == 'moderator' if result else False
    finally:
        conn.close()

@app.route('/check_moderator/<int:user_id>')
def check_moderator(user_id):
    is_moderator = get_user_role(user_id)
    # Return the result of the query as JSON
    return jsonify({'is_moderator': is_moderator})

if __name__ == '__main__':
    app.run(debug=True)