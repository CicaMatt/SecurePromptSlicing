from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Dummy function to simulate database insertion
def insert_user_message_in_db(username, message):
    print(f"Inserting into DB: User={username}, Message={message}")

# Route to handle the submission of a new message
@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

# Dummy function to simulate fetching messages from the database
def fetch_messages_from_db():
    return [
        {'username': 'user1', 'message': 'Hello!'},
        {'username': 'user2', 'message': 'Hi there!'}
    ]

# Main route to display messages
@app.route('/')
def main():
    messages = fetch_messages_from_db()
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
            <li><strong>{{ message.username }}</strong>: {{ message.message }}</li>
        {% endfor %}
    </ul>
    <form action="/post" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required>
        <br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" required></textarea>
        <br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>