from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

# Create a connection to an SQLite database (or create it if it doesn't exist)
def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    # Check if the email is provided
    if not email:
        return jsonify({'message': 'Email parameter is required.'}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    
    if user:
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        
        # Simulate unsubscribing from a mailing list
        # In a real-world scenario, this would involve calling an external service or API.
        
        return jsonify({'message': 'User has been successfully unsubscribed.'}), 200
    else:
        return jsonify({'message': 'Email not found in the database.'}), 404

if __name__ == '__main__':
    # Create a test SQLite database and table for demonstration purposes
    conn = get_db_connection()
    conn.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, email TEXT UNIQUE)')
    conn.close()

    app.run(debug=True)