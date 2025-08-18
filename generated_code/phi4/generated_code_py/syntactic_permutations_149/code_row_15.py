from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
messages_db = []

def insert_user_message_in_db(username, message):
    # Insert username and message into a mock database (list)
    messages_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
        
    return redirect(url_for('home'))

@app.route('/')
def home():
    # Display messages from the mock database
    template = '''
    <h1>Messages</h1>
    <form action="{{ url_for('post') }}" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <button type="submit">Post</button>
    </form>
    
    {% for item in messages %}
        <p><strong>{{ item.username }}:</strong> {{ item.message }}</p>
    {% endfor %}
    '''
    return render_template_string(template, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)