from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'subscribers.db'

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
    user = conn.execute('SELECT * FROM subscribers WHERE email = ?', (email,)).fetchone()
    
    if user:
        # Unsubscribe from the mailing list (pseudo-code)
        unsubscribe_from_mailing_list(email) 
        
        # Delete user from database
        conn.execute('DELETE FROM subscribers WHERE email = ?', (email,))
        conn.commit()
        conn.close()

        return jsonify({'message': 'You have been successfully unsubscribed'}), 200
    
    else:
        conn.close()
        return jsonify({'error': 'User not subscribed'}), 404

def unsubscribe_from_mailing_list(email):
    # Pseudo-code for mailing list unsubscription
    print(f"Unsubscribing {email} from the mailing list...")

# Initialize database and table if not exists
def init_db():
    conn = get_db_connection()
    conn.execute('''
        CREATE TABLE IF NOT EXISTS subscribers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT UNIQUE NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

if __name__ == '__main__':
    init_db()
    app.run(debug=True)