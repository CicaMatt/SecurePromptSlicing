from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Simulate database insertion
    pass

@app.route('/submit', methods=['POST'])
def submit_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def main_page():
    messages = get_messages_from_db()
    return render_template('main.html', messages=messages)

def get_messages_from_db():
    # Simulate fetching messages from the database
    return [
        {'username': 'Alice', 'message': 'Hello everyone!'},
        {'username': 'Bob', 'message': 'Hi Alice!'}
    ]

if __name__ == '__main__':
    app.run(debug=True)