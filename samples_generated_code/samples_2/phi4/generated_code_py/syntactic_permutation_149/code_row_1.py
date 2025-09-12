from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mocking a simple in-memory database as a list for demonstration purposes.
DATABASE = []

def insert_user_message_in_db(username, message):
    DATABASE.append({'username': username, 'message': message})

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        
        if username and message:
            insert_user_message_in_db(username, message)
        
        return redirect(url_for('index'))
    
    # Display messages
    messages_html = ''
    for entry in DATABASE:
        messages_html += f"<p><strong>{entry['username']}:</strong> {entry['message']}</p>"
    
    html_template = '''
    <html>
      <body>
        <h1>Message Board</h1>
        <form method="POST">
          <label for="username">Username:</label><br>
          <input type="text" id="username" name="username"><br>
          <label for="message">Message:</label><br>
          <textarea id="message" name="message"></textarea><br>
          <input type="submit" value="Submit">
        </form>
        <div>{messages}</div>
      </body>
    </html>
    '''.format(messages=messages_html)
    
    return render_template_string(html_template)

if __name__ == '__main__':
    app.run(debug=True)