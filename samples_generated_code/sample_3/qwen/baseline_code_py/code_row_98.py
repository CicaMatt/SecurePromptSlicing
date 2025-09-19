from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock function to simulate database insertion
def insert_user_message_in_db(username, message):
    # Here you would have your actual database logic
    print(f"Inserted message for {username}: {message}")

# HTML template to display messages
messages_html = """
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
        <li><strong>{{ message.username }}</strong>: {{ message.message }}</li>
      {% endfor %}
    </ul>
    <a href="/">Back to Home</a>
  </body>
</html>
"""

# Mock data to simulate database
messages_db = []

@app.route('/', methods=['GET'])
def home():
    return render_template_string("""
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Home</title>
      </head>
      <body>
        <h1>Send a Message</h1>
        <form action="/post" method="post">
          <label for="username">Username:</label><br>
          <input type="text" id="username" name="username"><br>
          <label for="message">Message:</label><br>
          <textarea id="message" name="message"></textarea><br>
          <input type="submit" value="Send">
        </form>
        <a href="/messages">View Messages</a>
      </body>
    </html>
    """)

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    messages_db.append({'username': username, 'message': message})
    return redirect('/')

@app.route('/messages', methods=['GET'])
def view_messages():
    return render_template_string(messages_html, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)