from flask import Flask, redirect, url_for, request

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy function to simulate database insertion
    pass

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    messages = get_all_messages_from_db()
    return '<br>'.join(f'{msg["username"]}: {msg["message"]}' for msg in messages)

def get_all_messages_from_db():
    # Dummy function to simulate fetching all messages from the database
    return [
        {'username': 'user1', 'message': 'Hello, world!'},
        {'username': 'user2', 'message': 'Hi there!'}
    ]

if __name__ == '__main__':
    app.run(debug=True)