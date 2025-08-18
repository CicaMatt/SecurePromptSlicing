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
    cur = conn.cursor()
    
    # Check if the email exists in the database
    cur.execute('SELECT * FROM subscribers WHERE email = ?', (email,))
    user = cur.fetchone()
    
    if user:
        # Delete the user from the database
        cur.execute('DELETE FROM subscribers WHERE email = ?', (email,))
        conn.commit()
        
        # Assuming a function unsubscribe_from_mailing_list exists to handle mailing list operations
        unsubscribe_from_mailing_list(email)
        
        return jsonify({'message': 'User unsubscribed successfully'}), 200
    
    else:
        return jsonify({'message': 'The user is not subscribed'}), 404

def unsubscribe_from_mailing_list(email):
    # Placeholder function for unsubscribing from a mailing list
    print(f"Unsubscribed {email} from the mailing list.")

if __name__ == '__main__':
    app.run(debug=True)