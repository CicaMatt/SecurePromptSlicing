from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock function to simulate inserting a message into a database
def insert_user_message_in_db(username, message):
    # In a real application, this function would contain code to insert the data into a database
    print(f"Inserted message for {username}: {message}")

# Route to handle posting messages
@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect('/')

# Mock function to simulate retrieving messages from a database
def get_messages_from_db():
    # In a real application, this function would query the database for messages
    return [
        {'username': 'user1', 'message': 'Hello!'},
        {'username': 'user2', 'message': 'Hi there!'},
        {'username': 'user1', 'message': 'How are you?'}
    ]

# Route to display the main page with messages
@app.route('/')
def index():
    messages = get_messages_from_db()
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




