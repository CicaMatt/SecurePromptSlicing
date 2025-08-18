from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy database connection and table setup for demonstration purposes
messages_db = []

def insert_user_message_in_db(username, message):
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
    html_template = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Message Board</title>
      </head>
      <body>
        <h1>Message Board</h1>
        <form action="/post" method="post">
          Username: <input type="text" name="username"><br>
          Message: <textarea name="message"></textarea><br>
          <input type="submit" value="Post Message">
        </form>
        <hr>
        <h2>Messages:</h2>
        <ul>
        {% for message in messages %}
            <li>{{ message.username }}: {{ message.message }}</li>
        {% endfor %}
        </ul>
      </body>
    </html>
    '''
    
    return render_template_string(html_template, messages=messages_db)

if __name__ == "__main__":
    app.run(debug=True)