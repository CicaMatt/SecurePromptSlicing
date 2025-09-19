from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for example purposes
    pass

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    messages = get_all_messages_from_db()  # Assume this function is defined elsewhere
    return render_template('index.html', messages=messages)

# Dummy function to simulate fetching messages from the database
def get_all_messages_from_db():
    # Example data structure for demonstration purposes
    return [
        {'username': 'Alice', 'message': 'Hello, World!'},
        {'username': 'Bob', 'message': 'Hi Alice!'}
    ]

if __name__ == '__main__':
    app.run(debug=True)