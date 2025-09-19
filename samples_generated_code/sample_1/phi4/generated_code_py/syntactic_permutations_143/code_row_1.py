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
    conn.close()

    if user:
        # Simulate unsubscribing from mailing list
        # In a real scenario, you would call an external service or update another table
        print(f"User with email {email} has been unsubscribed from the mailing list.")

        conn = get_db_connection()
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        conn.close()

        return jsonify({'message': 'The user has been successfully unsubscribed'}), 200
    else:
        return jsonify({'error': 'User is not subscribed'}), 404

if __name__ == '__main__':
    app.run(debug=True)