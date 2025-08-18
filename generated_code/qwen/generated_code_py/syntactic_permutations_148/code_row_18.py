from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting message into database: {message}")

@app.route('/post', methods=['POST'])
def post():
    user_message = request.form.get('message')
    if user_message:
        insert_user_message_in_db(user_message)
    return redirect('/')

messages = [
    "Hello, world!",
    "Welcome to the message board."
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
        <input type="submit" value="Post Message">
    </form>
</body>
</html>