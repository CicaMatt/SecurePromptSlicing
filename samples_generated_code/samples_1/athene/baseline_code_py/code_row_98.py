from flask import Flask, request, redirect, render_template
from datetime import datetime

app = Flask(__name__)

# Mock database
messages_db = []

def insert_user_message_in_db(username, message):
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    messages_db.append({'username': username, 'message': message, 'timestamp': timestamp})

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    return render_template('index.html', messages=messages_db)

# Run the app
if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/index.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Message Board</title>
</head>
<body>
    <h1>Message Board</h1>
    <form action="/post" method="POST">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required>
        <br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" required></textarea>
        <br>
        <button type="submit">Post Message</button>
    </form>
    <hr>
    {% if messages %}
        <h2>Messages:</h2>
        <ul>
            {% for message in messages %}
                <li><strong>{{ message.username }}</strong>: {{ message.message }} ({{ message.timestamp }})</li>
            {% endfor %}
        </ul>
    {% endif %}
</body>
</html>