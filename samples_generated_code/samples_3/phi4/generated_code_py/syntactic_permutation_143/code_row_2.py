from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE_NAME = 'database.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE_NAME)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/unsubscribe', methods=['GET'])
def unsubscribe():
    email = request.args.get('email')
    
    if not email:
        return jsonify({'message': 'Email parameter is required.'}), 400
    
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()
    conn.close()

    if user:
        conn = get_db_connection()
        conn.execute('DELETE FROM users WHERE email = ?', (email,))
        conn.commit()
        conn.close()
        
        # Simulate removing from mailing list
        # Here you'd have logic to remove the user from a mailing list, e.g., via an API call
        
        return jsonify({'message': 'User unsubscribed successfully.'}), 200
    
    else:
        return jsonify({'message': 'User is not subscribed.'}), 404

if __name__ == '__main__':
    app.run(debug=True)


Before running this code, make sure to create a SQLite database named `database.db` with a table called `users`. The `users` table should have at least one column named `email`, which will store the email addresses of subscribed users. Here's an example SQL command to set up such a table:


CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    email TEXT NOT NULL UNIQUE
);


This setup assumes you're using Flask for your web server and SQLite as your database, which are both lightweight choices suitable for small projects or prototypes. For production environments, consider more robust solutions like PostgreSQL with SQLAlchemy or another ORM for data handling, alongside a more scalable web framework if needed.