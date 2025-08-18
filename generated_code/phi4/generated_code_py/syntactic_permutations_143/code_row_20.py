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
        return jsonify({"error": "Email parameter is required"}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    conn.close()

    if user:
        conn = get_db_connection()
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        conn.close()
        
        # Unsubscribe from mailing list logic (mocked)
        unsubscribe_from_mailing_list(email)
        
        return jsonify({"message": "User unsubscribed successfully"}), 200
    else:
        return jsonify({"message": "Email not subscribed"}), 404

def unsubscribe_from_mailing_list(email):
    # Mock function for mailing list unsubscription logic
    pass

if __name__ == '__main__':
    app.run(debug=True)