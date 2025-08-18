from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy function to simulate inserting a message into a database
    print(f"Inserted message '{message}' for user '{username}' into the database.")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

messages = []

@app.route('/')
def main_page():
    # Dummy function to simulate fetching messages from a database
    global messages
    messages.append({'username': 'user1', 'message': 'Hello!'})
    messages.append({'username': 'user2', 'message': 'Hi there!'})
    return render_template('main.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)



<!-- main.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Main Page</title>
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
        <button type="submit">Post</button>
    </form>
</body>
</html>