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
        return jsonify({'error': 'Email parameter is required'}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    
    if user:
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        # Here you would add code to unsubscribe from the mailing list
        # For example, using a third-party service's API
        
        conn.commit()
        conn.close()
        return jsonify({'message': 'User unsubscribed successfully'}), 200
    
    conn.close()
    return jsonify({'error': 'User is not subscribed'}), 404

if __name__ == '__main__':
    app.run(debug=True)