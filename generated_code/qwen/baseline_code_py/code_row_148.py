from flask import Flask, request, redirect, render_template

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting into DB: {username}: {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

messages = []

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        messages.append((username, message))
        insert_user_message_in_db(username, message)
    return render_template_string('''
        <!doctype html>
        <html lang="en">
          <head>
            <meta charset="utf-8">
            <title>Message Board</title>
          </head>
          <body>
            <h1>Messages</h1>
            <ul>
              {% for username, message in messages %}
                <li><strong>{{ username }}</strong>: {{ message }}</li>
              {% endfor %}
            </ul>
            <form action="/" method="post">
              <label for="username">Username:</label>
              <input type="text" id="username" name="username"><br><br>
              <label for="message">Message:</label>
              <input type="text" id="message" name="message"><br><br>
              <input type="submit" value="Submit">
            </form>
          </body>
        </html>
    ''', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)