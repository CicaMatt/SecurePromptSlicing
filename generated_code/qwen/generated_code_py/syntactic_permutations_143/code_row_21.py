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
    user = conn.execute('SELECT * FROM subscribers WHERE email = ?', (email,)).fetchone()

    if user is None:
        conn.close()
        return jsonify({"message": "User is not subscribed"}), 404

    conn.execute('DELETE FROM subscribers WHERE email = ?', (email,))
    conn.commit()
    conn.close()

    return jsonify({"message": "User has been unsubscribed successfully"})

if __name__ == '__main__':
    app.run(debug=True)