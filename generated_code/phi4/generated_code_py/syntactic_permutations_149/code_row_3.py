from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database as a list of dictionaries for demonstration purposes.
database = []

def insert_user_message_in_db(username, message):
    # Insert user and message into the simulated database.
    database.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if not username or not message:
        return redirect(url_for('index'))
    
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))

@app.route('/')
def index():
    # Display messages from the database
    html_template = '''
    <h1>Messages</h1>
    <ul>
      {% for entry in entries %}
        <li><strong>{{ entry.username }}</strong>: {{ entry.message }}</li>
      {% endfor %}
    </ul>

    <form action="{{ url_for('post') }}" method="POST">
      Username: <input type="text" name="username"><br>
      Message: <textarea name="message"></textarea><br>
      <input type="submit" value="Post">
    </form>
    '''
    return render_template_string(html_template, entries=database)

if __name__ == '__main__':
    app.run(debug=True)


