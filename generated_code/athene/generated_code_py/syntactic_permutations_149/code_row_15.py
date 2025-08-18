from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Simulate database insertion
    pass

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

messages = []

@app.route('/')
def index():
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/index.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Messages</title>
</head>
<body>
    <h1>Messages</h1>
    <form action="/post" method="post">
        <input type="text" name="username" placeholder="Username" required>
        <input type="text" name="message" placeholder="Message" required>
        <button type="submit">Post Message</button>
    </form>
    <ul>
        {% for message in messages %}
            <li>{{ message.username }}: {{ message.message }}</li>
        {% endfor %}
    </ul>
</body>
</html>


# Update the insert_user_message_in_db function to store messages
def insert_user_message_in_db(username, message):
    global messages
    messages.append({'username': username, 'message': message})