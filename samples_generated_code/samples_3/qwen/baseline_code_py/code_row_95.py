from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock function to simulate inserting a message into a database
def insert_user_message_in_db(username, message):
    # In a real application, this function would contain code to insert the data into a database
    print(f"Inserted message for {username}: {message}")

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect('/')

# Mock data to simulate messages in a database
messages = [
    {'username': 'Alice', 'message': 'Hello, World!'},
    {'username': 'Bob', 'message': 'This is a test message.'}
]

@app.route('/')
def index():
    # Render messages on the home page
    return render_template_string('''
        <h1>Messages</h1>
        <ul>
            {% for msg in messages %}
                <li><strong>{{ msg.username }}</strong>: {{ msg.message }}</li>
            {% endfor %}
        </ul>
        <form action="/post" method="post">
            <input type="text" name="username" placeholder="Username" required>
            <br>
            <textarea name="message" placeholder="Message" required></textarea>
            <br>
            <button type="submit">Post Message</button>
        </form>
    ''', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)