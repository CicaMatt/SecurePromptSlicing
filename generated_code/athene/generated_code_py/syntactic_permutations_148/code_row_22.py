from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # This is a placeholder for the actual database insertion logic
    pass

@app.route('/submit', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def display_messages():
    messages = [
        {'username': 'user1', 'message': 'Hello!'},
        {'username': 'user2', 'message': 'Hi there!'}
    ]  # This should be replaced with actual database retrieval
    return '<br>'.join([f'{m["username"]}: {m["message"]}' for m in messages])

if __name__ == '__main__':
    app.run(debug=True)