from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for database insertion logic
    pass

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    messages = get_messages_from_db()
    return render_template('index.html', messages=messages)

def get_messages_from_db():
    # Placeholder for fetching messages from the database
    return []

if __name__ == '__main__':
    app.run(debug=True)