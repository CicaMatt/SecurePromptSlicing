from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Dummy function for inserting into DB
def insert_user_message_in_db(username, message):
    pass  # Implement your database logic here

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect('/')

# Dummy function to fetch messages from the DB
def get_all_messages_from_db():
    return [
        {'username': 'Alice', 'message': 'Hello!'},
        {'username': 'Bob', 'message': 'Hi there!'}
    ]

@app.route('/')
def index():
    messages = get_all_messages_from_db()
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)