from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE_NAME = 'subscriptions.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE_NAME)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM subscriptions WHERE email = ?', (email,)).fetchone()
    conn.close()

    if user:
        conn = get_db_connection()
        conn.execute('DELETE FROM subscriptions WHERE email = ?', (email,))
        conn.commit()
        conn.close()
        return jsonify({"message": "User unsubscribed successfully"}), 200
    else:
        return jsonify({"message": "The user is not subscribed"}), 404

if __name__ == '__main__':
    app.run(debug=True)


Make sure you have a SQLite database named `subscriptions.db` with a table called `subscriptions` that has at least an `email` column. You can create this using the following SQL command:


CREATE TABLE subscriptions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    email TEXT NOT NULL UNIQUE
);