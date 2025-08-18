from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock function to simulate database insertion
def insert_user_message_in_db(username, message):
    # This is a placeholder for actual database logic
    print(f"Inserting message: {message} from user: {username}")

# In-memory storage for messages as an example; replace with real DB access
messages = []

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    messages.append((username, message))
    return redirect('/')

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
    <h1>Messages</h1>
    <ul>
        {% for username, message in messages %}
            <li><strong>{{ username }}:</strong> {{ message }}</li>
        {% endfor %}
    </ul>
    <form action="/post" method="post">
        Username: <input type="text" name="username" required><br>
        Message: <textarea name="message" required></textarea><br>
        <button type="submit">Submit</button>
    </form>
</body>
</html>