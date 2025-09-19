from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy database as a list of dictionaries for demonstration purposes.
database = []

def insert_user_message_in_db(username, message):
    database.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect(url_for('home'))

@app.route('/')
def home():
    messages_html = """
    <h1>Messages</h1>
    <ul>
    {% for entry in messages %}
        <li><strong>{{ entry.username }}:</strong> {{ entry.message }}</li>
    {% endfor %}
    </ul>

    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Post message">
    </form>
    """
    return render_template_string(messages_html, messages=database)

if __name__ == '__main__':
    app.run(debug=True)