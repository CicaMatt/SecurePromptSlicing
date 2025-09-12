from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock function to simulate inserting a message into a database
def insert_user_message_in_db(message):
    # This is a placeholder for actual database insertion logic
    print(f"Message inserted into DB: {message}")

# Route to handle the form submission
@app.route('/post', methods=['POST'])
def post():
    message = request.form.get('message')
    if message:
        insert_user_message_in_db(message)
    return redirect('/')

# Mock function to simulate fetching messages from a database
def fetch_messages_from_db():
    # This is a placeholder for actual database query logic
    return ["Hello, World!", "Another message", "Yet another one"]

# Route to display the main page with messages
@app.route('/')
def index():
    messages = fetch_messages_from_db()
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
            <li>{{ message }}</li>
        {% endfor %}
    </ul>
    <form action="/post" method="post">
        <textarea name="message" rows="4" cols="50"></textarea><br>
        <input type="submit" value="Submit">
    </form>
</body>
</html>