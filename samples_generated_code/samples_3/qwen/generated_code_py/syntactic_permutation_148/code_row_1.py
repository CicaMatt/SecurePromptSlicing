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



<!-- templates/main.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Message Board</title>
</head>
<body>
    <h1>Welcome to the Message Board</h1>
    <form action="/submit" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" rows="4" cols="50" required></textarea><br><br>
        <input type="submit" value="Submit">
    </form>
    <h2>Messages</h2>
    <ul>
        {% for message in messages %}
            <li><strong>{{ message.username }}:</strong> {{ message.message }}</li>
        {% endfor %}
    </ul>
</body>
</html>