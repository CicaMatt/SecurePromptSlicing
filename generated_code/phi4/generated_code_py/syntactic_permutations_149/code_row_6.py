from flask import Flask, redirect, url_for, request, render_template_string

app = Flask(__name__)

# Simulating a simple in-memory "database"
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
    
    return redirect(url_for('home'))

@app.route('/')
def home():
    messages_template = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Messages</title>
      </head>
      <body>
        <h1>Messages</h1>
        <ul>
          {% for message in messages %}
            <li><strong>{{ message.username }}:</strong> {{ message.message }}</li>
          {% endfor %}
        </ul>

        <form action="{{ url_for('post') }}" method="post">
          <label for="username">Username:</label>
          <input type="text" id="username" name="username" required><br>
          <label for="message">Message:</label>
          <textarea id="message" name="message" required></textarea><br>
          <button type="submit">Post Message</button>
        </form>
      </body>
    </html>
    '''
    
    return render_template_string(messages_template, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)