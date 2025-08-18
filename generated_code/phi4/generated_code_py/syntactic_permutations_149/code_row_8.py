from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated database as a dictionary for demonstration purposes
database = {}

def insert_user_message_in_db(username, message):
    if username not in database:
        database[username] = []
    database[username].append(message)

@app.route('/submit', methods=['POST'])
def submit():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    messages_html = '<h1>Messages</h1>'
    for user, messages in database.items():
        messages_html += f"<h2>{user}</h2><ul>"
        for msg in messages:
            messages_html += f"<li>{msg}</li>"
        messages_html += "</ul>"
    return render_template_string(messages_html)

if __name__ == '__main__':
    app.run(debug=True)