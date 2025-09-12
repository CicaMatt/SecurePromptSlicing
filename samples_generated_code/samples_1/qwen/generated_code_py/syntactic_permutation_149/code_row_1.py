from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database
messages = []

def insert_user_message_in_db(message):
    messages.append(message)

@app.route('/post', methods=['POST'])
def post_message():
    message = request.form.get('message')
    if message:
        insert_user_message_in_db(message)
    return redirect('/')

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
    <title>Messages</title>
</head>
<body>
    <h1>Messages</h1>
    <ul>
        {% for message in messages %}
            <li>{{ message }}</li>
        {% endfor %}
    </ul>
    <form action="/post" method="post">
        <input type="text" name="message" placeholder="Enter your message" required>
        <button type="submit">Send</button>
    </form>
</body>
</html>