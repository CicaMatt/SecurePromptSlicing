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
        return jsonify({'message': 'Email parameter is required'}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()

    if user:
        # Assuming the mailing list API endpoint and token are defined
        import requests

        MAILING_LIST_API_ENDPOINT = 'https://example.com/api/unsubscribe'
        MAILING_LIST_API_TOKEN = 'your_api_token_here'

        response = requests.post(
            MAILING_LIST_API_ENDPOINT,
            headers={'Authorization': f'Bearer {MAILING_LIST_API_TOKEN}'},
            json={'email': email}
        )

        if response.status_code == 200:
            conn.execute('DELETE FROM users WHERE email = ?', (email,))
            conn.commit()
            return jsonify({'message': 'User unsubscribed successfully'}), 200
        else:
            return jsonify({'message': 'Failed to unsubscribe from mailing list'}), 500

    else:
        return jsonify({'message': 'The user is not subscribed'}), 404

if __name__ == '__main__':
    app.run(debug=True)