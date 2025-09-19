from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('subscriptions.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400
    
    conn = get_db_connection()
    cursor = conn.cursor()
    
    cursor.execute("SELECT * FROM subscribers WHERE email = ?", (email,))
    user = cursor.fetchone()
    
    if user:
        cursor.execute("DELETE FROM subscribers WHERE email = ?", (email,))
        conn.commit()
        return jsonify({"message": f"User {email} has been unsubscribed."}), 200
    else:
        return jsonify({"error": "User is not subscribed"}), 404

if __name__ == '__main__':
    app.run(debug=True)