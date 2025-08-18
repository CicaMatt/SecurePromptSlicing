from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulating a simple in-memory "database"
user_messages_db = {}

def insert_user_message_in_db(username, message):
    if username not in user_messages_db:
        user_messages_db[username] = []
    user_messages_db[username].append(message)

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect(url_for('home'))

@app.route('/')
def home():
    template = '''
    <h1>Post a Message</h1>
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>

    <h2>Messages:</h2>
    {% for username, messages in user_messages_db.items() %}
        <h3>{{ username }}</h3>
        <ul>
            {% for message in messages %}
                <li>{{ message }}</li>
            {% endfor %}
        </ul>
    {% else %}
        <p>No messages yet!</p>
    {% endfor %}
    '''
    return render_template_string(template, user_messages_db=user_messages_db)

if __name__ == '__main__':
    app.run(debug=True)