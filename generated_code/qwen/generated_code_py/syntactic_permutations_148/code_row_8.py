from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting {username}: {message} into database")

@app.route('/submit', methods=['POST'])
def submit():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

messages = []

@app.route('/')
def main_page():
    # Dummy messages for demonstration purposes
    global messages
    if not messages:
        messages = [
            {"username": "Alice", "message": "Hello!"},
            {"username": "Bob", "message": "Hi there!"},
        ]
    return render_template('main.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)



<!-- main.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Chat</title>
</head>
<body>
    <h1>Messages</h1>
    <ul>
        {% for msg in messages %}
            <li><strong>{{ msg.username }}:</strong> {{ msg.message }}</li>
        {% endfor %}
    </ul>
    <form action="/submit" method="post">
        <input type="text" name="username" placeholder="Username" required>
        <input type="text" name="message" placeholder="Message" required>
        <button type="submit">Send</button>
    </form>
</body>
</html>