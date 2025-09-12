from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database storage
messages_db = []

def insert_user_message_in_db(username, message):
    global messages_db
    messages_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect(url_for('home'))

@app.route('/')
def home():
    messages_html = render_template_string("""
    <h1>Messages</h1>
    <ul>
    {% for entry in messages %}
        <li><strong>{{ entry.username }}:</strong> {{ entry.message }}</li>
    {% endfor %}
    </ul>

    <form action="{{ url_for('post') }}" method="POST">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Post">
    </form>
    """, messages=messages_db)
    return messages_html

if __name__ == '__main__':
    app.run(debug=True)