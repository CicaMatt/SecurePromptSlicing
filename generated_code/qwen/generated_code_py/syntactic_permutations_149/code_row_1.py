from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # This is a placeholder function for demonstration purposes.
    # In a real application, this would interact with a database.
    print(f"Inserting message from {username}: {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

messages = []

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        messages.append((username, message))
        insert_user_message_in_db(username, message)
    return render_template_string('''
        <form method="post" action="/">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Send">
        </form>
        <h2>Messages:</h2>
        <ul>
            {% for username, message in messages %}
                <li><strong>{{ username }}</strong>: {{ message }}</li>
            {% endfor %}
        </ul>
    ''')

if __name__ == '__main__':
    app.run(debug=True)