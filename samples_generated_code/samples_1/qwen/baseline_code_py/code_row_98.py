from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database representation for demonstration purposes
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    return render_template('index.html', messages=messages_db)

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
            <li><strong>{{ message.username }}:</strong> {{ message.message }}</li>
        {% endfor %}
    </ul>
    <form action="/post" method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required>
        <br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" required></textarea>
        <br>
        <button type="submit">Send</button>
    </form>
</body>
</html>