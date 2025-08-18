from flask import Flask, request, redirect, url_for, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder function for inserting data into a database
    print(f"Inserting {username}: {message} into the database")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

messages = [
    {"username": "user1", "message": "Hello!"},
    {"username": "user2", "message": "Hi there!"}
]

@app.route('/')
def main():
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)



<!-- index.html -->
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
            <li><strong>{{ message.username }}:</strong> {{ message.message }}</li>
        {% endfor %}
    </ul>
    <form action="{{ url_for('post') }}" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" required></textarea><br><br>
        <button type="submit">Send</button>
    </form>
</body>
</html>