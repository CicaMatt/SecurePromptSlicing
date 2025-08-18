from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy function to simulate database insertion
    print(f"Inserting message for {username}: {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))

@app.route('/')
def index():
    # Dummy data to simulate messages from the database
    messages = [
        {'username': 'Alice', 'message': 'Hello!'},
        {'username': 'Bob', 'message': 'Hi there!'}
    ]
    html = """
    <h1>Messages</h1>
    <ul>
    {% for message in messages %}
        <li><strong>{{ message.username }}:</strong> {{ message.message }}</li>
    {% endfor %}
    </ul>
    <form action="{{ url_for('post') }}" method="post">
        Username: <input type="text" name="username"><br>
        Message: <input type="text" name="message"><br>
        <input type="submit" value="Post Message">
    </form>
    """
    return render_template_string(html, messages=messages)

if __name__ == '__main__':
    app.run(debug=True)