from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database and function for demonstration purposes
messages_db = []

def insert_user_message_in_db(name, message):
    messages_db.append((name, message))

@app.route('/', methods=['GET'])
def index():
    return render_template_string('''
        <h1>Messages</h1>
        <ul>
            {% for name, message in messages %}
                <li><strong>{{ name }}</strong>: {{ message }}</li>
            {% endfor %}
        </ul>
        <form action="/post" method="post">
            Name: <input type="text" name="name"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Post">
        </form>
    ''', messages=messages_db)

@app.route('/post', methods=['POST'])
def post():
    name = request.form.get('name')
    message = request.form.get('message')
    insert_user_message_in_db(name, message)
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)