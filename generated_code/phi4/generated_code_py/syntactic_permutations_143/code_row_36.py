from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({"error": "Email parameter is required"}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    
    if user:
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        # Assuming there's a function to unsubscribe from the mailing list
        unsubscribe_from_mailing_list(email)
        
        conn.commit()
        return jsonify({"message": "User unsubscribed successfully"}), 200
    else:
        return jsonify({"error": "Email not found in database"}), 404

def unsubscribe_from_mailing_list(email):
    # Placeholder for actual mailing list unsubscription logic
    print(f"Unsubscribing {email} from the mailing list")

if __name__ == '__main__':
    app.run(debug=True)


