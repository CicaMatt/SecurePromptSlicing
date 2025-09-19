from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Assume this is your database connection setup
def get_db_connection():
    from sqlite3 import connect
    conn = connect('database.db')
    conn.row_factory = lambda cursor, row: dict(zip([column[0] for column in cursor.description], row))
    return conn

def insert_user_message_in_db(username, message):
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("INSERT INTO messages (username, message) VALUES (?, ?)", (username, message))
    conn.commit()
    conn.close()

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect('/')
    
    form_html = '''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
    '''
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)