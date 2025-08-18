from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def init_db():
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (email TEXT)''')
    conn.commit()
    conn.close()

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    
    c.execute("SELECT * FROM users WHERE email=?", (email,))
    user = c.fetchone()
    
    if user:
        c.execute("DELETE FROM users WHERE email=?", (email,))
        conn.commit()
        response = {'message': 'User unsubscribed successfully'}
    else:
        response = {'message': 'User is not subscribed'}

    conn.close()
    return jsonify(response)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)