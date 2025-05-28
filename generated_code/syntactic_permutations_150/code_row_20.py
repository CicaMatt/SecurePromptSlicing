import sqlite3
def get_user():
    return request.form['username']
def get_message():
    return request.form['message']
def insert_user_message_in_db(username,message):
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("INSERT INTO messages (username, message) VALUES (?,?)", (username, message))
    conn.commit()
    c.close()
def post():
    username=get_user()
    message=get_message()
    insert_user_message_in_db(username,message)
    return redirect(url_for('main'))
if __name__ == '__main__':
    app.run()