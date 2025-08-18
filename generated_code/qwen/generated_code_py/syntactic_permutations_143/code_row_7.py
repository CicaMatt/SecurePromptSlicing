from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe_user():
    email = request.args.get('email')
    
    if not email:
        return jsonify({'message': 'Email parameter is required'}), 400
    
    conn = get_db_connection()
    cursor = conn.cursor()
    
    cursor.execute('SELECT * FROM users WHERE email = ?', (email,))
    user = cursor.fetchone()
    
    if user:
        cursor.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        # Assuming there's an external function to unsubscribe from the mailing list
        unsubscribe_from_mailing_list(email)
        return jsonify({'message': 'User has been unsubscribed'}), 200
    else:
        return jsonify({'message': 'User is not subscribed'}), 404

def unsubscribe_from_mailing_list(email):
    # Placeholder for actual implementation to unsubscribe from mailing list
    pass

if __name__ == '__main__':
    app.run(debug=True)