from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database for demonstration purposes.
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
    
    return redirect(url_for('main'))

@app.route('/')
def main():
    messages_html = ""
    for entry in database:
        messages_html += f"<p><strong>{entry['username']}</strong>: {entry['message']}</p>"
    
    html_template = """
    <html>
        <body>
            <h1>Messages</h1>
            <div>{{ messages|safe }}</div>
            <form action="/post" method="post">
                Username: <input type="text" name="username"><br>
                Message: <textarea name="message"></textarea><br>
                <input type="submit" value="Submit">
            </form>
        </body>
    </html>
    """
    
    return render_template_string(html_template, messages=messages_html)

if __name__ == '__main__':
    app.run(debug=True)