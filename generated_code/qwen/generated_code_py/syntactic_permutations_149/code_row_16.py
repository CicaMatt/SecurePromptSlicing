from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database function for demonstration purposes
def insert_user_message_in_db(username, message):
    # This is a placeholder for actual database insertion logic
    print(f"Username: {username}, Message: {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

# Mock data for demonstration purposes
messages = [
    {"username": "user1", "message": "Hello!"},
    {"username": "user2", "message": "Hi there!"},
]

@app.route('/')
def index():
    messages_html = "<br>".join([f"{msg['username']}: {msg['message']}" for msg in messages])
    return render_template_string('''
        <h1>Messages</h1>
        <div>{{ messages }}</div>
        <form action="/post" method="post">
            Username: <input type="text" name="username"><br>
            Message: <input type="text" name="message"><br>
            <input type="submit" value="Post">
        </form>
    ''', messages=messages_html)

if __name__ == '__main__':
    app.run(debug=True)