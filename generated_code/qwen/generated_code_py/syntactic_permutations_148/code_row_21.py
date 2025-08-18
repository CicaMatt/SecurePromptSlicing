from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock function to simulate database insertion
def insert_user_message_in_db(username, message):
    # In a real application, this function would interact with a database
    print(f"Inserted message from {username}: {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

# Mock function to simulate fetching messages from the database
def fetch_messages_from_db():
    # In a real application, this function would query a database for messages
    return [
        {"username": "user1", "message": "Hello!"},
        {"username": "user2", "message": "Hi there!"},
    ]

@app.route('/')
def main_page():
    messages = fetch_messages_from_db()
    return render_template('main.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)



<!-- main.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Message Board</title>
</head>
<body>
    <h1>Messages</h1>
    <ul>
        {% for message in messages %}
            <li><strong>{{ message.username }}:</strong> {{ message.message }}</li>
        {% endfor %}
    </ul>
    <form action="/post" method="post">
        <input type="text" name="username" placeholder="Username" required>
        <br>
        <textarea name="message" placeholder="Message" required></textarea>
        <br>
        <button type="submit">Post</button>
    </form>
</body>
</html>