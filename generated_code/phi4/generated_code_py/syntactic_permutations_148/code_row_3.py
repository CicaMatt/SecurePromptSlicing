from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy database simulation with a list
database_messages = []

def insert_user_message_in_db(username, message):
    global database_messages
    database_messages.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect(url_for('main'))

@app.route('/')
def main():
    messages_html = '<br>'.join([f"{msg['username']}: {msg['message']}" for msg in database_messages])
    return render_template_string(f"""
        <h1>Main Page</h1>
        <form action="/post" method="post">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
        <h2>Messages:</h2>
        <div>{messages_html}</div>
    """)

if __name__ == '__main__':
    app.run(debug=True)