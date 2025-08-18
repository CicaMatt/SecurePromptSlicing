from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database as a list of dictionaries for demonstration purposes.
messages_db = []

def insert_user_message_in_db(username, message):
    # Insert the username and message into our mock 'database'.
    messages_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    # Get the username and message from the request form data.
    username = request.form.get('username')
    message = request.form.get('message')

    if username and message:
        insert_user_message_in_db(username, message)

    # Redirect to the home page after posting a message.
    return redirect('/')

@app.route('/')
def index():
    # Render the messages from our mock 'database'.
    messages_html = '<h1>Messages</h1>'
    for entry in messages_db:
        messages_html += f"<p><strong>{entry['username']}</strong>: {entry['message']}</p>"
    
    return render_template_string(messages_html)

if __name__ == '__main__':
    app.run(debug=True)