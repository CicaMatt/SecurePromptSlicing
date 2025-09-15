from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"User: {username}, Message: {message} inserted into database.")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

messages = []

@app.route('/')
def index():
    # Dummy data for demonstration purposes
    global messages
    if not messages:
        messages = [
            {"username": "Alice", "message": "Hello, world!"},
            {"username": "Bob", "message": "Hi there!"},
        ]
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




