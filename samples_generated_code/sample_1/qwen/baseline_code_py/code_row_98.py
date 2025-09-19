from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock function for demonstration purposes
def insert_user_message_in_db(username, message):
    # This should contain actual database insertion logic
    print(f"Inserted message from {username}: {message}")

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect('/')

# Mock function for demonstration purposes
def get_messages_from_db():
    # This should contain actual database retrieval logic
    return [
        {'username': 'user1', 'message': 'Hello!'},
        {'username': 'user2', 'message': 'Hi there!'}
    ]

@app.route('/')
def display_messages():
    messages = get_messages_from_db()
    return render_template('messages.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Messages</title>
</head>
<body>
    <h1>Messages</h1>
    <ul>
        {% for message in messages %}
            <li><strong>{{ message.username }}</strong>: {{ message.message }}</li>
        {% endfor %}
    </ul>
    <form action="/post" method="post">
        <input type="text" name="username" placeholder="Username" required>
        <textarea name="message" placeholder="Message" required></textarea>
        <button type="submit">Post</button>
    </form>
</body>
</html>