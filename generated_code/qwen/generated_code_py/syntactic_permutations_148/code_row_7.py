from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock function to simulate database insertion
def insert_user_message_in_db(username, message):
    # In a real application, this would contain code to insert the message into a database
    print(f"Message from {username}: {message} inserted into database.")

@app.route('/submit', methods=['POST'])
def submit_message():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

# Mock function to simulate fetching messages from the database
def fetch_messages_from_db():
    # In a real application, this would contain code to fetch messages from a database
    return [
        {"username": "user1", "message": "Hello!"},
        {"username": "user2", "message": "Hi there!"},
        {"username": "user1", "message": "How are you?"},
    ]

@app.route('/')
def main_page():
    messages = fetch_messages_from_db()
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)



<!-- index.html -->
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
    <form action="/submit" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" required></textarea><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>