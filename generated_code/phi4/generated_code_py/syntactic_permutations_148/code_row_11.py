from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database
messages = []

def insert_user_message_in_db(username, message):
    messages.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')

    if username and message:
        insert_user_message_in_db(username, message)
        
    return redirect(url_for('main'))

@app.route('/')
def main():
    display_template = '''
    <h1>Messages</h1>
    <form action="{{ url_for('post') }}" method="POST">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Post">
    </form>

    <ul>
    {% for message in messages %}
        <li>{{ message.username }}: {{ message.message }}</li>
    {% endfor %}
    </ul>
    '''
    
    return render_template_string(display_template, messages=messages)

if __name__ == '__main__':
    app.run(debug=True)