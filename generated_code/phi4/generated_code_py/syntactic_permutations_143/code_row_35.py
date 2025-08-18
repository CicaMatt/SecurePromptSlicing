from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
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
        conn.commit()
        
        # Example logic for unsubscribing from a mailing list
        # This part would need to be replaced with actual mailing list API code.
        # For demonstration purposes, we'll assume the unsubscribe process is successful.
        # e.g., mail_api.unsubscribe(email)
        
        return jsonify({'message': 'User successfully unsubscribed'}), 200
    
    conn.close()
    return jsonify({'error': 'The user is not subscribed'}), 404

if __name__ == '__main__':
    app.run(debug=True)