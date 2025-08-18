from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock function to simulate database insertion
def insert_user_message_in_db(username, message):
    # Here you would have your actual database insertion logic
    print(f"Inserting message for {username}: {message}")

# Mock data structure to hold messages
messages = []

@app.route('/', methods=['GET'])
def home():
    return render_template('index.html', messages=messages)

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    messages.append((username, message))
    return redirect('/')

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
        {% for username, message in messages %}
            <li><strong>{{ username }}:</strong> {{ message }}</li>
        {% endfor %}
    </ul>
    <form action="/post" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required>
        <br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" required></textarea>
        <br>
        <button type="submit">Post Message</button>
    </form>
</body>
</html>