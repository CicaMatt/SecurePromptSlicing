from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy function to simulate database insertion
    print(f"Inserting message for {username}: {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

messages = [
    {"username": "user1", "message": "Hello!"},
    {"username": "user2", "message": "Hi there!"},
]

@app.route('/')
def index():
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/index.html -->
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
        <br>
        <textarea name="message" placeholder="Message" required></textarea>
        <br>
        <button type="submit">Send</button>
    </form>
</body>
</html>