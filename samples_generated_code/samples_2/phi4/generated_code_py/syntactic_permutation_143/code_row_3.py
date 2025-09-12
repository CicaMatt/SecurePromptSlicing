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
    cursor = conn.cursor()
    user = cursor.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    
    if user:
        cursor.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        # Assuming a separate function or logic handles mailing list unsubscription
        return jsonify({'message': f'User with email {email} unsubscribed successfully'}), 200
    else:
        return jsonify({'message': 'The user is not subscribed'}), 404

if __name__ == '__main__':
    app.run(debug=True)