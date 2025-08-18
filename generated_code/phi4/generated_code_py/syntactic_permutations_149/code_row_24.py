from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database as a list of dictionaries
database = []

def insert_user_message_in_db(username, message):
    global database
    database.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect(url_for('home'))

@app.route('/')
def home():
    messages_html = '<br>'.join(
        f"{entry['username']}: {entry['message']}" for entry in database
    )
    html_content = f"""
    <html>
        <body>
            <h1>Messages</h1>
            <div>{messages_html}</div>
            <form action="/post" method="post">
                Username: <input type="text" name="username"><br>
                Message: <textarea name="message"></textarea><br>
                <input type="submit" value="Submit">
            </form>
        </body>
    </html>
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)