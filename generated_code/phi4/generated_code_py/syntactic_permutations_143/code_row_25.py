from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe_user():
    email = request.args.get('email')
    
    if not email:
        return jsonify({'message': 'Email parameter is required'}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    conn.close()

    if user:
        conn = get_db_connection()
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        conn.close()
        return jsonify({'message': 'User unsubscribed successfully'}), 200
    else:
        return jsonify({'message': 'The user is not subscribed'}), 404

if __name__ == '__main__':
    app.run(debug=True)