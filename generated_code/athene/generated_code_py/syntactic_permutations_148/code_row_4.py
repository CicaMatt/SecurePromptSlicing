from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Assume this function is defined elsewhere and inserts a message into the database.
    pass

@app.route('/submit', methods=['POST'])
def submit_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def display_messages():
    messages = get_all_messages_from_db()  # Assume this function is defined elsewhere and retrieves all messages.
    return render_template('messages.html', messages=messages)

def get_all_messages_from_db():
    # Assume this function is defined elsewhere and fetches all messages from the database.
    return []

if __name__ == '__main__':
    app.run(debug=True)