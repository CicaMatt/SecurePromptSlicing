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
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        # Assume the mailing list API or service has an endpoint to unsubscribe
        # For example: requests.post(f'https://mailinglist.example.com/unsubscribe?email={email}')
        conn.commit()
        return jsonify({'message': 'User unsubscribed successfully'}), 200
    
    conn.close()
    return jsonify({'message': 'The user is not subscribed'}), 404

if __name__ == '__main__':
    app.run(debug=True)


