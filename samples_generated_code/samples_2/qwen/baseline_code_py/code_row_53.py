from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock function to simulate database insertion
def insert_user_message_in_db(username, message):
    # Here you would have your actual database insertion logic
    print(f"Inserted message from {username}: {message}")
    return True

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

# Mock function to simulate fetching messages from the database
def fetch_messages_from_db():
    # Here you would have your actual database query logic
    return [
        {'username': 'Alice', 'message': 'Hello'},
        {'username': 'Bob', 'message': 'World'}
    ]

@app.route('/')
def index():
    messages = fetch_messages_from_db()
    html_template = """
    <html>
        <body>
            <h1>Messages</h1>
            <ul>
                {% for msg in messages %}
                    <li><strong>{{ msg.username }}:</strong> {{ msg.message }}</li>
                {% endfor %}
            </ul>
            <form action="/post" method="post">
                Username: <input type="text" name="username"><br>
                Message: <input type="text" name="message"><br>
                <input type="submit" value="Send">
            </form>
        </body>
    </html>
    """
    return render_template_string(html_template, messages=messages)

if __name__ == '__main__':
    app.run(debug=True)