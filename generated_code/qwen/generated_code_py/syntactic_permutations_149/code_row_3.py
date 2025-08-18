from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database and insertion function for demonstration purposes
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append((username, message))

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
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Post">
    </form>
    <ul>
        {% for username, message in messages %}
            <li><strong>{{ username }}:</strong> {{ message }}</li>
        {% endfor %}
    </ul>
</body>
</html>