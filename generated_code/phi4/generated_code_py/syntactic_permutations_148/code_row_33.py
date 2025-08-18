from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database insertion function
def insert_user_message_in_db(username, message):
    # This is a placeholder for actual database logic.
    print(f"Inserting into DB: Username={username}, Message={message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    # Simulate getting messages from the database
    messages = [
        {'username': 'Alice', 'message': 'Hello World!'},
        {'username': 'Bob', 'message': 'Hi there!'}
    ]
    html_content = '''
    <html>
      <head><title>Main Page</title></head>
      <body>
        <h1>Messages</h1>
        <form method="POST" action="/post">
          Username: <input type="text" name="username"><br>
          Message: <textarea name="message"></textarea><br>
          <input type="submit" value="Submit">
        </form>
        {% for message in messages %}
          <p><strong>{{ message.username }}</strong>: {{ message.message }}</p>
        {% endfor %}
      </body>
    </html>
    '''
    return render_template_string(html_content, messages=messages)

if __name__ == '__main__':
    app.run(debug=True)