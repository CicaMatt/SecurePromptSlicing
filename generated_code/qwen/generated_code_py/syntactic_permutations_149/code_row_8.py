from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database for demonstration purposes
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append((username, message))

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    return render_template('index.html', messages=messages_db)

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
    <h1>Leave a Message</h1>
    <form method="post">
        Username: <input type="text" name="username" required><br>
        Message: <textarea name="message" required></textarea><br>
        <button type="submit">Submit</button>
    </form>
    <h2>Messages</h2>
    <ul>
        {% for username, message in messages %}
            <li><strong>{{ username }}:</strong> {{ message }}</li>
        {% endfor %}
    </ul>
</body>
</html>