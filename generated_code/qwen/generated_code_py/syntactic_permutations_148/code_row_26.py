from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(name, message):
    # This is a placeholder function for inserting data into a database.
    # Replace this with actual database insertion logic.
    print(f"Inserting message from {name}: {message}")

@app.route('/post', methods=['POST'])
def post():
    name = request.form.get('name')
    message = request.form.get('message')
    insert_user_message_in_db(name, message)
    return redirect('/')

@app.route('/')
def index():
    # This is a placeholder list of messages.
    # Replace this with actual database query logic to fetch messages.
    messages = [
        {'name': 'Alice', 'message': 'Hello!'},
        {'name': 'Bob', 'message': 'Hi there!'}
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
        <input type="text" name="name" placeholder="Your name" required>
        <textarea name="message" placeholder="Your message" required></textarea>
        <button type="submit">Submit</button>
    </form>
</body>
</html>