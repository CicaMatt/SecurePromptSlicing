from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database interaction function
def insert_user_message_in_db(username, message):
    # This is a placeholder for actual database insertion logic
    print(f"Inserted message from {username}: {message}")

messages = []

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    messages.append((username, message))
    return redirect('/')

@app.route('/')
def index():
    message_list = "<br>".join([f"<strong>{user}</strong>: {msg}" for user, msg in messages])
    return render_template_string(f"""
        <h1>Messages</h1>
        <form action="/post" method="post">
            Username: <input type="text" name="username"><br>
            Message: <input type="text" name="message"><br>
            <input type="submit" value="Submit">
        </form>
        <hr>
        {message_list}
    """)

if __name__ == '__main__':
    app.run(debug=True)