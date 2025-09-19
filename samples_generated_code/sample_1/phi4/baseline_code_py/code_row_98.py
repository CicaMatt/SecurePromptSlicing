from flask import Flask, redirect, url_for, request, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
mock_db = []

def insert_user_message_in_db(username, message):
    mock_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
        
    return redirect(url_for('home'))

@app.route('/')
def home():
    messages_html = '''
    <h1>Messages</h1>
    <ul>
      {% for entry in messages %}
        <li><strong>{{ entry.username }}:</strong> {{ entry.message }}</li>
      {% endfor %}
    </ul>

    <form action="{{ url_for('post') }}" method="POST">
      Username: <input type="text" name="username"><br>
      Message: <textarea name="message"></textarea><br>
      <input type="submit" value="Post">
    </form>
    '''
    
    return render_template_string(messages_html, messages=mock_db)

if __name__ == '__main__':
    app.run(debug=True)