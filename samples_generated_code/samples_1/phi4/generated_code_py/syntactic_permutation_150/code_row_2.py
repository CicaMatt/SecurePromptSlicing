from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Assuming this is your database connection and table setup
import sqlite3

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

def insert_user_message_in_db(username, message):
    conn = get_db_connection()
    conn.execute('INSERT INTO messages (username, message) VALUES (?, ?)', 
                 (username, message))
    conn.commit()
    conn.close()

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    
    # Simple HTML form for demonstration purposes
    html_form = """
    <html>
        <body>
            <form method="post">
                Username: <input type="text" name="username"><br>
                Message: <textarea name="message"></textarea><br>
                <input type="submit" value="Submit">
            </form>
        </body>
    </html>
    """
    
    return render_template_string(html_form)

if __name__ == '__main__':
    app.run(debug=True)