from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"User: {username}, Message: {message} saved to database.")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

messages = []

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        messages.append((username, message))
        insert_user_message_in_db(username, message)
    message_list = '<br>'.join([f'<strong>{username}</strong>: {message}' for username, message in messages])
    return render_template_string('''
        <h1>Chat</h1>
        <form method="post" action="/">
            Username: <input type="text" name="username"><br>
            Message: <input type="text" name="message"><br>
            <input type="submit" value="Send">
        </form>
        <h2>Messages</h2>
        {{ messages }}
    ''', messages=message_list)

if __name__ == '__main__':
    app.run(debug=True)