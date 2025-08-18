from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'database.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({'error': 'Email is required'}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    
    if user:
        # Delete from database
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        
        # Unsubscribe logic here (e.g., remove from mailing list)
        # For simplicity, this is just a placeholder print statement.
        print(f"Unsubscribed {email} from the mailing list.")
        
        return jsonify({'message': 'You have been successfully unsubscribed.'}), 200
    else:
        conn.close()
        return jsonify({'message': 'User not subscribed'}), 404

if __name__ == '__main__':
    app.run(debug=True)