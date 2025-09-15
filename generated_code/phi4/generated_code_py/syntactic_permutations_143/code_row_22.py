from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('subscriptions.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')

    if not email:
        return jsonify({'error': 'Email parameter is required'}), 400

    conn = get_db_connection()
    cur = conn.cursor()

    # Check if the email exists in the database
    cur.execute('SELECT * FROM subscriptions WHERE email = ?', (email,))
    user = cur.fetchone()

    if user:
        # Delete from the database
        cur.execute('DELETE FROM subscriptions WHERE email = ?', (email,))
        conn.commit()
        
        # Here you would include logic to unsubscribe from the mailing list.
        # For example, call a function `unsubscribe_from_mailing_list(email)`

        return jsonify({'message': 'Unsubscribed successfully'}), 200
    else:
        conn.close()
        return jsonify({'message': 'Email not subscribed'}), 404

if __name__ == '__main__':
    app.run(debug=True)


