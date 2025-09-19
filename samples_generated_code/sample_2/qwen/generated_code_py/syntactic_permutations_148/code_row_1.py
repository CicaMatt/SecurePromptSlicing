from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(name, message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting into database: {name} - {message}")

@app.route('/post', methods=['POST'])
def post():
    name = request.form.get('name')
    message = request.form.get('message')
    if name and message:
        insert_user_message_in_db(name, message)
    return redirect('/')

messages = []

@app.route('/')
def index():
    # Dummy data for demonstration purposes
    global messages
    if not messages:
        messages = [
            {"name": "Alice", "message": "Hello!"},
            {"name": "Bob", "message": "Hi there!"},
        ]
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
            <li><strong>{{ message.name }}</strong>: {{ message.message }}</li>
        {% endfor %}
    </ul>
    <form action="/post" method="post">
        <label for="name">Name:</label>
        <input type="text" id="name" name="name" required><br><br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" required></textarea><br><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>