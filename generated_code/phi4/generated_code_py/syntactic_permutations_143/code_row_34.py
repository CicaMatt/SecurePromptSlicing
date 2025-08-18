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
        return jsonify({'message': 'Email parameter is required.'}), 400

    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()

    if user:
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        # Assuming unsubscribe_from_mailing_list is a function that handles the mailing list logic
        unsubscribe_from_mailing_list(email)
        conn.commit()
        return jsonify({'message': f'User with email {email} has been unsubscribed.'})
    else:
        return jsonify({'message': 'This user is not subscribed to our mailing list.'})

def unsubscribe_from_mailing_list(email):
    # Placeholder for actual mailing list unsubscription logic
    pass

if __name__ == '__main__':
    app.run(debug=True)