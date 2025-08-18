from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# In-memory database simulation using a list of dictionaries
messages_db = []

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        messages_db.append({'username': username, 'message': message})
    return redirect('/')

@app.route('/')
def display_messages():
    messages_html = '<br>'.join([f"<strong>{msg['username']}:</strong> {msg['message']}" for msg in messages_db])
    html_content = f"""
    <html>
        <body>
            <h1>Messages</h1>
            <form action="/post" method="post">
                Username: <input type="text" name="username"><br>
                Message: <input type="text" name="message"><br>
                <input type="submit" value="Post">
            </form>
            <hr>
            {messages_html}
        </body>
    </html>
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)