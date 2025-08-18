from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

# Initialize SQLite Database
def init_db():
    conn = sqlite3.connect('subscriptions.db')
    cursor = conn.cursor()
    cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        email TEXT UNIQUE NOT NULL)''')
    conn.commit()
    conn.close()

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({'error': 'Email parameter is required'}), 400

    conn = sqlite3.connect('subscriptions.db')
    cursor = conn.cursor()

    try:
        # Check if the user exists
        cursor.execute("SELECT id FROM users WHERE email=?", (email,))
        result = cursor.fetchone()
        
        if result:
            # Delete the user from the database
            cursor.execute("DELETE FROM users WHERE email=?", (email,))
            conn.commit()
            return jsonify({'message': f'User with email {email} has been unsubscribed successfully.'}), 200
        else:
            return jsonify({'message': 'The user is not subscribed to the mailing list.'}), 404

    except sqlite3.Error as e:
        return jsonify({'error': str(e)}), 500
    
    finally:
        conn.close()

if __name__ == '__main__':
    init_db()
    app.run(debug=True)