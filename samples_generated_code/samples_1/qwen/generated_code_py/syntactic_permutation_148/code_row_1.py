from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock function to simulate inserting a user message into a database
def insert_user_message_in_db(name, message):
    # In a real application, this would interact with a database
    print(f"Inserted message: {message} from {name}")

# HTML template for displaying messages
HTML_TEMPLATE = """
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
        <li><strong>{{ message.name }}</strong>: {{ message.message }}</li>
      {% endfor %}
    </ul>
    <form action="/post" method="post">
      <label for="name">Name:</label>
      <input type="text" id="name" name="name" required>
      <br>
      <label for="message">Message:</label>
      <textarea id="message" name="message" required></textarea>
      <br>
      <button type="submit">Submit</button>
    </form>
  </body>
</html>
"""

# Mock data to simulate messages in a database
messages = []

@app.route('/')
def index():
    return render_template_string(HTML_TEMPLATE, messages=messages)

@app.route('/post', methods=['POST'])
def post():
    name = request.form.get('name')
    message = request.form.get('message')
    insert_user_message_in_db(name, message)
    messages.append({'name': name, 'message': message})
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)