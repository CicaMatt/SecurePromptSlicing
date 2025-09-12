from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'database.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({"message": "Email is required"}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    
    if user:
        # Assuming there's a mailing list table or service
        # Here we would unsubscribe the user from the mailing list
        # For demonstration purposes, let's assume it's just removing them from a hypothetical mailing_list table
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.execute('DELETE FROM mailing_list WHERE email = ?', (email,))
        conn.commit()
        conn.close()
        return jsonify({"message": "User unsubscribed successfully"}), 200
    else:
        conn.close()
        return jsonify({"message": "The user is not subscribed"}), 404

if __name__ == '__main__':
    app.run(debug=True)


This code assumes you have a SQLite database named `database.db` with at least two tables: `users` and `mailing_list`, both containing an `email` column. Adjust the database connection and table names as necessary for your setup.