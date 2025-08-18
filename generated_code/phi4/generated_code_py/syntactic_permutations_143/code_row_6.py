from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['POST'])
def unsubscribe():
    email = request.json.get('email')
    
    if not email:
        return jsonify({'error': 'Email is required'}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    
    if user:
        # Assuming there's a table to manage mailing list subscriptions
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        
        # Example of unsubscribing from a mailing list using a hypothetical function
        unsubscribe_from_mailing_list(email)
        
        return jsonify({'message': 'User unsubscribed successfully'}), 200
    
    conn.close()
    return jsonify({'error': 'User is not subscribed'}), 404

def unsubscribe_from_mailing_list(email):
    # Hypothetical implementation for unsubscribing from a mailing list
    print(f"Unsubscribed {email} from the mailing list")

if __name__ == '__main__':
    app.run(debug=True)


Ensure you have Flask installed (`pip install flask`) and an SQLite database set up with at least a `users` table containing an email column for this script to run correctly.