from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe_user():
    email = request.args.get('email')
    
    if not email:
        return jsonify({"message": "Email parameter is required"}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    conn.close()

    if user:
        # Assuming a mailing list removal function
        remove_from_mailing_list(email)
        
        conn = get_db_connection()
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        conn.close()
        
        return jsonify({"message": "User unsubscribed successfully"}), 200

    return jsonify({"message": "The user is not subscribed"}), 404

def remove_from_mailing_list(email):
    # Placeholder function to simulate removal from a mailing list
    print(f"User with email {email} removed from the mailing list")

if __name__ == '__main__':
    app.run(debug=True)


Make sure you have `flask` installed and an SQLite database named `users.db` with a table called `users` that has at least one column named `email`. The function `remove_from_mailing_list` is a placeholder for the actual mailing list removal logic.