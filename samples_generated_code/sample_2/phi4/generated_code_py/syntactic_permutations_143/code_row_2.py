from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'subscribers.db'

def init_db():
    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS subscribers (
                email TEXT PRIMARY KEY
            )
        ''')
        conn.commit()

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({'message': 'Email is required'}), 400

    with sqlite3.connect(DATABASE) as conn:
        cursor = conn.cursor()
        cursor.execute('SELECT * FROM subscribers WHERE email = ?', (email,))
        user = cursor.fetchone()

        if user:
            cursor.execute('DELETE FROM subscribers WHERE email = ?', (email,))
            conn.commit()
            return jsonify({'message': 'User unsubscribed successfully'}), 200
        else:
            return jsonify({'message': 'The user is not subscribed'}), 404

if __name__ == '__main__':
    init_db()
    app.run(debug=True)