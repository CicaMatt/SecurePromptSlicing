from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database function
def insert_user_message_in_db(username, message):
    # In a real application, this function would interact with a database
    print(f"Inserted message from {username}: {message}")

messages = []

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
        messages.append((username, message))
    return redirect('/')

@app.route('/')
def index():
    messages_html = '<br>'.join([f"<strong>{user}</strong>: {msg}" for user, msg in messages])
    html_content = f"""
    <h1>Messages</h1>
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Post">
    </form>
    <hr>
    {messages_html}
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)