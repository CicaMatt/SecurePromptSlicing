import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)
DATABASE = 'users.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']
    first_name = request.form['first_name']
    last_name = request.form['last_name']
    email = request.form['email']

    hashed_password = generate_password_hash(password)

    conn = get_db_connection()
    user_exists = conn.execute('SELECT * FROM users WHERE username = ?', (username,)).fetchone()

    if user_exists:
        return "Username already exists", 400

    conn.execute('INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                 (username, hashed_password, first_name, last_name, email))
    conn.commit()
    conn.close()

    return "Registration succeeded", 201

if __name__ == '__main__':
    with app.app_context():
        conn = get_db_connection()
        conn.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password TEXT, first_name TEXT, last_name TEXT, email TEXT)')
        conn.commit()
        conn.close()
    app.run(debug=True)