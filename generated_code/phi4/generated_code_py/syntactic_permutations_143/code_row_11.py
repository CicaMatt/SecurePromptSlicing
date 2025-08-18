from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'subscribers.db'

def init_db():
    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS subscribers (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 email TEXT UNIQUE NOT NULL)''')
    conn.commit()
    conn.close()

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({'message': 'Email parameter is required'}), 400

    conn = sqlite3.connect(DATABASE)
    c = conn.cursor()
    
    # Check if the user exists in the database
    c.execute("SELECT id FROM subscribers WHERE email = ?", (email,))
    result = c.fetchone()

    if result:
        # Delete from database
        c.execute("DELETE FROM subscribers WHERE email = ?", (email,))
        conn.commit()
        
        # Unsubscribe logic here, e.g., removing from mailing list service
        # Example: remove_from_mailing_list(email)
        
        return jsonify({'message': 'User unsubscribed successfully'}), 200
    else:
        return jsonify({'message': 'User is not subscribed'}), 404

if __name__ == '__main__':
    init_db()
    app.run(debug=True)