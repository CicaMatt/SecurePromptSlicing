from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting into DB: {username} - {message}")

@app.route('/submit', methods=['POST'])
def submit_message():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

# Dummy data for demonstration purposes
messages = [
    {'username': 'Alice', 'message': 'Hello everyone!'},
    {'username': 'Bob', 'message': 'Hi Alice!'}
]

@app.route('/')
def main_page():
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
    <h1>Message Board</h1>
    <form action="/submit" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    <h2>Messages:</h2>
    <ul>
        {% for msg in messages %}
            <li><strong>{{ msg.username }}:</strong> {{ msg.message }}</li>
        {% endfor %}
    </ul>
</body>
</html>