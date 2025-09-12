from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database
messages = []

def insert_user_message_in_db(username, message):
    messages.append({'username': username, 'message': message})

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)



<!-- templates/index.html -->
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Message Board</title>
</head>
<body>
    <h1>Leave a Message</h1>
    <form method="post">
        <label for="username">Username:</label>
        <input type="text" id="username" name="username" required><br><br>
        <label for="message">Message:</label>
        <textarea id="message" name="message" rows="4" cols="50" required></textarea><br><br>
        <button type="submit">Submit</button>
    </form>

    <h2>Messages</h2>
    <ul>
        {% for message in messages %}
            <li><strong>{{ message.username }}:</strong> {{ message.message }}</li>
        {% endfor %}
    </ul>
</body>
</html>