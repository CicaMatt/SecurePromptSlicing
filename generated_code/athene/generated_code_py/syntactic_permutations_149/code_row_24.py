from flask import Flask, request, redirect, render_template
from datetime import datetime

app = Flask(__name__)

# Simulating a database
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

if __name__ == '__main__':
    app.run(debug=True)


# Create a templates/index.html file with the following content:
"""
<html>
<head>
    <title>Message Board</title>
</head>
<body>
    <h1>Message Board</h1>
    <form action="/post" method="post">
        <input type="text" name="username" placeholder="Username" required>
        <input type="text" name="message" placeholder="Message" required>
        <button type="submit">Post Message</button>
    </form>
    <ul>
        {% for message in messages %}
            <li>{{ message.timestamp }} - {{ message.username }}: {{ message.message }}</li>
        {% endfor %}
    </ul>
</body>
</html>
"""