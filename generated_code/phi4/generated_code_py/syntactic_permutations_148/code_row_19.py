from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated database as a list of dictionaries for demonstration purposes
database = []

def insert_user_message_in_db(username, message):
    """Inserts user message into the simulated database."""
    database.append({"username": username, "message": message})

@app.route('/post', methods=['POST'])
def post():
    """Handles posting of messages by users."""
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
    
    return redirect('/')

@app.route('/')
def main_page():
    """Displays the main page with all user messages."""
    html_content = """
    <!doctype html>
    <html lang="en">
      <head>
        <title>Message Board</title>
      </head>
      <body>
        <h1>Post a Message</h1>
        <form action="/post" method="POST">
          Username: <input type="text" name="username"><br>
          Message: <textarea name="message"></textarea><br>
          <input type="submit" value="Submit">
        </form>

        <h2>Messages</h2>
        <ul>
    """
    for entry in database:
        html_content += f"<li><strong>{entry['username']}</strong>: {entry['message']}</li>\n"
    
    html_content += """
        </ul>
      </body>
    </html>
    """
    return render_template_string(html_content)

if __name__ == '__main__':
    app.run(debug=True)