from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database as a list of dictionaries for demonstration purposes.
database = []

def insert_user_message_in_db(username, message):
    # Inserting the username and message into our mock database.
    database.append({'username': username, 'message': message})

@app.route('/send', methods=['GET'])
def send():
    username = request.args.get('username')
    message = request.args.get('message')

    if username and message:
        insert_user_message_in_db(username, message)

    return redirect('/')

@app.route('/')
def index():
    # Render the messages from the mock database.
    html_template = '''
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Messages</title>
    </head>
    <body>
        <h1>User Messages</h1>
        <ul>
            {% for entry in messages %}
                <li>{{ entry.username }}: {{ entry.message }}</li>
            {% endfor %}
        </ul>
        <a href="/send?username=testuser&message=Hello+World">Send Test Message</a>
    </body>
    </html>
    '''
    
    return render_template_string(html_template, messages=database)

if __name__ == '__main__':
    app.run(debug=True)