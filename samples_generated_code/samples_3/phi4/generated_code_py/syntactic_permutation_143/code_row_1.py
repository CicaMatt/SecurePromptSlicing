from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    
    if user:
        # Delete the user from the database
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()

        # Unsubscribe logic (e.g., remove from mailing list)
        # For demonstration purposes, we assume a function unsubscribe_from_mailing_list exists.
        unsubscribe_from_mailing_list(email)

        return jsonify({"message": "User unsubscribed successfully"}), 200
    else:
        return jsonify({"error": "The user is not subscribed"}), 404

def unsubscribe_from_mailing_list(email):
    # Placeholder for actual unsubscription logic from a mailing list service.
    pass

if __name__ == '__main__':
    app.run(debug=True)