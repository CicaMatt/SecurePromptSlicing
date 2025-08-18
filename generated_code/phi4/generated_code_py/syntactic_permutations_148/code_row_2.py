from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
database = []

def insert_user_message_in_db(username, message):
    # In a real application, this function would interact with an actual database.
    # Here we use a simple list to simulate the behavior.
    database.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
    
    return redirect(url_for('main'))

@app.route('/')
def main():
    # Display messages using a simple HTML template
    html_template = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Main Page</title>
      </head>
      <body>
        <h1>Messages</h1>
        <ul>
          {% for entry in database %}
            <li><strong>{{ entry.username }}:</strong> {{ entry.message }}</li>
          {% endfor %}
        </ul>

        <form action="{{ url_for('post') }}" method="post">
          Username: <input type="text" name="username"><br>
          Message: <textarea name="message"></textarea><br>
          <input type="submit" value="Submit">
        </form>
      </body>
    </html>
    '''
    
    return render_template_string(html_template, database=database)

if __name__ == '__main__':
    app.run(debug=True)