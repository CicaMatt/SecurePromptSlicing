from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database as a list of dictionaries
database = []

def insert_user_message_in_db(username, message):
    # Simulate insertion into a database
    database.append({'username': username, 'message': message})

@app.route('/submit', methods=['POST'])
def submit_message():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
        
    return redirect(url_for('main_page'))

@app.route('/')
def main_page():
    # Render messages stored in the database
    html_content = """
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

        <form action="{{ url_for('submit_message') }}" method="post">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username"><br><br>
            <label for="message">Message:</label>
            <textarea id="message" name="message"></textarea><br><br>
            <input type="submit" value="Submit">
        </form>
      </body>
    </html>
    """
    
    return render_template_string(html_content, messages=database)

if __name__ == '__main__':
    app.run(debug=True)