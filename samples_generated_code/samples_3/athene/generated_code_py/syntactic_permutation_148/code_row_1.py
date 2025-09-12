from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    pass

@app.route('/submit', methods=['POST'])
def submit_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def main_page():
    messages = get_messages_from_db()  # Assume this function retrieves all messages
    return render_template('main.html', messages=messages)

def get_messages_from_db():
    # Dummy implementation for demonstration purposes
    return [
        {'username': 'user1', 'message': 'Hello, world!'},
        {'username': 'user2', 'message': 'How are you?'}
    ]

if __name__ == '__main__':
    app.run(debug=True)