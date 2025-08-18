from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
messages_db = []

def insert_user_message_in_db(name, message):
    global messages_db
    messages_db.append({'name': name, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    name = request.form.get('name')
    message = request.form.get('message')
    if name and message:
        insert_user_message_in_db(name, message)
    return redirect('/')

@app.route('/')
def index():
    messages_html = "<h1>Messages</h1>"
    for entry in messages_db:
        messages_html += f"<p><strong>{entry['name']}:</strong> {entry['message']}</p>"
    return render_template_string(messages_html)

if __name__ == '__main__':
    app.run(debug=True)