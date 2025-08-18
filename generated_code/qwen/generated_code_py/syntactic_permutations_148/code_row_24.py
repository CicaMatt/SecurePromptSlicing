from flask import Flask, request, redirect, url_for, render_template

app = Flask(__name__)

# Mock function to simulate database insertion
def insert_user_message_in_db(username, message):
    # In a real application, this function would interact with a database
    print(f"Inserted message: {message} by user: {username}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))

# Mock function to simulate fetching messages from the database
def get_messages_from_db():
    # In a real application, this function would query the database for messages
    return [
        {'username': 'user1', 'message': 'Hello!'},
        {'username': 'user2', 'message': 'Hi there!'}
    ]

@app.route('/')
def index():
    messages = get_messages_from_db()
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/index.html -->
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
    <form action="{{ url_for('post') }}" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" required></textarea><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>