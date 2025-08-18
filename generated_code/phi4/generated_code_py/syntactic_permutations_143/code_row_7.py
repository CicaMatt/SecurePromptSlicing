from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({'error': 'Email parameter is required'}), 400

    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    conn.close()

    if user:
        # Simulate unsubscribing from mailing list
        unsubscribe_from_mailing_list(email)

        # Delete user from the database
        conn = get_db_connection()
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        conn.close()
        
        return jsonify({'message': 'User has been unsubscribed and deleted'}), 200

    return jsonify({'message': 'The user is not subscribed'}), 404

def unsubscribe_from_mailing_list(email):
    # Placeholder function to simulate mailing list unsubscription
    pass

if __name__ == '__main__':
    app.run(debug=True)