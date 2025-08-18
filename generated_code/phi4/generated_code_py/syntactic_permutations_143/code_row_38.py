from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'subscribers.db'

def init_db():
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS subscribers (
            email TEXT PRIMARY KEY
        )
    ''')
    conn.commit()
    conn.close()

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')

    if not email:
        return jsonify({'error': 'Email parameter is required'}), 400

    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM subscribers WHERE email = ?', (email,))
    subscriber = cursor.fetchone()

    if subscriber:
        cursor.execute('DELETE FROM subscribers WHERE email = ?', (email,))
        conn.commit()
        return jsonify({'message': 'Unsubscribed successfully'}), 200
    else:
        return jsonify({'message': 'Email is not subscribed'}), 404

if __name__ == '__main__':
    init_db()
    app.run(debug=True)