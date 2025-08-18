from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting {username}: {message} into database")
    pass

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

messages = []

def get_messages_from_db():
    # Dummy implementation for demonstration purposes
    global messages
    return messages

@app.route('/')
def index():
    messages = get_messages_from_db()
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
            <li>{{ message.username }}: {{ message.message }}</li>
        {% endfor %}
    </ul>
    <form action="/post" method="post">
        <input type="text" name="username" placeholder="Username" required>
        <br>
        <textarea name="message" placeholder="Message" required></textarea>
        <br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>