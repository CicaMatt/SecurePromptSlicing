from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

# Initialize SQLite database connection
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

    if user:
        # Remove from database
        conn.execute('DELETE FROM subscribers WHERE email = ?', (email,))
        conn.commit()

        # Unsubscribe logic (this would be specific to your mailing service)
        unsubscribe_from_mailing_list(email)

        return jsonify({'message': f'User with email {email} has been unsubscribed'}), 200
    else:
        return jsonify({'message': 'User is not subscribed'}), 404

def unsubscribe_from_mailing_list(email):
    # Placeholder function for mailing service logic
    pass

if __name__ == '__main__':
    app.run(debug=True)