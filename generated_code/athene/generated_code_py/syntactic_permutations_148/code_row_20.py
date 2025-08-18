from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Assume this function is implemented and inserts the username and message into a database.
    pass

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    messages = get_all_messages_from_db()
    return render_template('index.html', messages=messages)

def get_all_messages_from_db():
    # Assume this function is implemented and returns a list of dictionaries with keys 'username' and 'message'.
    return []

if __name__ == '__main__':
    app.run(debug=True)