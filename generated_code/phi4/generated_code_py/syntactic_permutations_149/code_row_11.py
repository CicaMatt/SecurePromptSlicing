from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulating a simple in-memory 'database'
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    template = '''
        <h1>Messages</h1>
        <form method="post" action="/post">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Post">
        </form>
        <ul>
            {% for entry in messages %}
                <li>{{ entry.username }} says: {{ entry.message }}</li>
            {% endfor %}
        </ul>
    '''
    return render_template_string(template, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)