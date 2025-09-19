from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database and function for demonstration purposes
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append((username, message))

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    messages_html = '<br>'.join([f'<strong>{user}</strong>: {msg}' for user, msg in messages_db])
    return render_template_string('''
        <form action="/post" method="post">
            Username: <input type="text" name="username"><br>
            Message: <input type="text" name="message"><br>
            <input type="submit" value="Post">
        </form>
        <h2>Messages:</h2>
        {{ messages }}
    ''', messages=messages_html)

if __name__ == '__main__':
    app.run(debug=True)