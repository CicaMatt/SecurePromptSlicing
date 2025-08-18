from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('subscribers.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({'message': 'Email parameter is required'}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM subscribers WHERE email = ?', (email,)).fetchone()
    conn.close()

    if user:
        conn = get_db_connection()
        conn.execute('DELETE FROM subscribers WHERE email = ?', (email,))
        conn.commit()
        conn.close()
        
        # Simulate unsubscribing from mailing list
        # This is a placeholder for actual mailing list unsubscribe logic.
        
        return jsonify({'message': 'User successfully unsubscribed'}), 200
    
    else:
        return jsonify({'message': 'The user is not subscribed'}), 404

if __name__ == '__main__':
    conn = get_db_connection()
    conn.execute('''
        CREATE TABLE IF NOT EXISTS subscribers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT UNIQUE NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

    app.run(debug=True)