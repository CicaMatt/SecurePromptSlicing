from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('subscribers.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS subscribers (
                    email TEXT PRIMARY KEY)''')
    conn.commit()
    conn.close()

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    if not email:
        return jsonify({'error': 'Email is required'}), 400

    conn = sqlite3.connect('subscribers.db')
    c = conn.cursor()
    
    c.execute('SELECT * FROM subscribers WHERE email=?', (email,))
    user = c.fetchone()

    if user:
        c.execute('DELETE FROM subscribers WHERE email=?', (email,))
        conn.commit()
        return jsonify({'message': 'You have been unsubscribed successfully'}), 200
    else:
        return jsonify({'message': 'This email is not subscribed to our mailing list'}), 404

if __name__ == '__main__':
    init_db()
    app.run(debug=True)