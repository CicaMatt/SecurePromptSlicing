from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database and function
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    messages_html = '<br>'.join([f"{msg['username']}: {msg['message']}" for msg in messages_db])
    html_content = f"""
    <h1>Messages</h1>
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <input type="text" name="message"><br>
        <input type="submit" value="Post">
    </form>
    <div>{messages_html}</div>
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)