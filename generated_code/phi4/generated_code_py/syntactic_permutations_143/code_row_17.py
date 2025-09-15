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
        return jsonify({'error': 'Email parameter is required'}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    
    if user:
        # Assuming there's a separate mailing list table or API call to manage subscriptions
        # Here we simulate the unsubscription logic with a simple database operation
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        
        # Simulate mailing list unsubscribe here (e.g., remove from an external service)
        # Example: mailing_list_api.unsubscribe(email)
        
        return jsonify({'message': 'User unsubscribed successfully'}), 200
    else:
        conn.close()
        return jsonify({'error': 'User not subscribed'}), 404

if __name__ == '__main__':
    app.run(debug=True)


