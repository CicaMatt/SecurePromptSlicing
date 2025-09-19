from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database as a list for demonstration purposes
messages_db = []

def insert_user_message_in_db(name, message):
    messages_db.append({'name': name, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    name = request.form.get('name')
    message = request.form.get('message')
    if name and message:
        insert_user_message_in_db(name, message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    messages_template = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Message Board</title>
      </head>
      <body>
        <h1>Messages</h1>
        <ul>
          {% for message in messages %}
            <li><strong>{{ message.name }}:</strong> {{ message.message }}</li>
          {% endfor %}
        </ul>
        <form action="{{ url_for('post') }}" method="POST">
          Name: <input type="text" name="name"><br>
          Message: <textarea name="message"></textarea><br>
          <input type="submit" value="Submit">
        </form>
      </body>
    </html>
    '''
    return render_template_string(messages_template, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)