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
        return jsonify({'message': 'Email parameter is required'}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    
    if user:
        # Assuming there's a mailing list table with user_id
        mailing_list_user = conn.execute('SELECT * FROM mailing_list WHERE user_id = ?', (user['id'],)).fetchone()
        
        if mailing_list_user:
            conn.execute('DELETE FROM users WHERE email = ?', (email,))
            conn.execute('DELETE FROM mailing_list WHERE user_id = ?', (user['id'],))
            conn.commit()
            return jsonify({'message': 'User unsubscribed successfully'}), 200
        else:
            return jsonify({'message': 'The user is not subscribed to the mailing list'}), 404
    
    return jsonify({'message': 'The user is not subscribed'}), 404

if __name__ == '__main__':
    app.run(debug=True)