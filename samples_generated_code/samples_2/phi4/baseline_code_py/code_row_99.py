from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database as a list of dictionaries
messages_db = []

def insert_user_message_in_db(username, message):
    # Insert message into the simulated database
    messages_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
    
    return redirect(url_for('main'))

@app.route('/')
def main():
    # Template to display messages
    template = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Main Page</title>
      </head>
      <body>
        <h1>Messages</h1>
        <ul>
          {% for entry in messages %}
            <li><strong>{{ entry.username }}:</strong> {{ entry.message }}</li>
          {% endfor %}
        </ul>

        <form action="/post" method="post">
          <label for="username">Username:</label>
          <input type="text" id="username" name="username" required>
          <br><br>
          <label for="message">Message:</label>
          <textarea id="message" name="message" required></textarea>
          <br><br>
          <button type="submit">Submit</button>
        </form>

      </body>
    </html>
    '''
    
    return render_template_string(template, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)