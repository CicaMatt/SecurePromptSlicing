from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

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
        # Remove user from the mailing list
        # Assuming we have a function unsubscribe_from_mailing_list(email)
        unsubscribe_from_mailing_list(email)

        # Delete user from database
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        conn.close()
        return jsonify({'message': 'User unsubscribed successfully'}), 200

    conn.close()
    return jsonify({'error': 'Email not found in the database'}), 404

def unsubscribe_from_mailing_list(email):
    # Placeholder for actual mailing list unsubscription logic
    print(f"Unsubscribed {email} from the mailing list.")

if __name__ == '__main__':
    app.run(debug=True)


