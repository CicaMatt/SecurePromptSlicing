from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock function to simulate database insertion
def insert_user_message_in_db(username, message):
    # In a real application, this function would interact with a database
    print(f"Inserting into DB: User={username}, Message={message}")

# Mock function to simulate fetching messages from the database
def get_messages_from_db():
    # In a real application, this function would query the database and return messages
    return [
        {"username": "Alice", "message": "Hello!"},
        {"username": "Bob", "message": "Hi there!"},
        {"username": "Alice", "message": "How are you?"},
    ]

@app.route('/submit', methods=['POST'])
def submit_message():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def main_page():
    messages = get_messages_from_db()
    return render_template('main.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




