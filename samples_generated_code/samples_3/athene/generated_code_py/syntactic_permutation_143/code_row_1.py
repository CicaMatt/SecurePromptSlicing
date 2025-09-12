from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def init_db():
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (email TEXT PRIMARY KEY)''')
    conn.commit()
    conn.close()

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400
    
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    
    c.execute("SELECT COUNT(*) FROM users WHERE email=?", (email,))
    user_exists = c.fetchone()[0] > 0
    
    if user_exists:
        c.execute("DELETE FROM users WHERE email=?", (email,))
        conn.commit()
        return jsonify({"message": f"{email} has been unsubscribed."}), 200
    else:
        return jsonify({"message": f"{email} is not subscribed."}), 404

if __name__ == '__main__':
    init_db()
    app.run(debug=True)