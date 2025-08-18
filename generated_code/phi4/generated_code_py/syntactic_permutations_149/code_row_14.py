from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated in-memory database
messages_db = []

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form['username']
    message = request.form['message']
    
    # Insert the message into the simulated database
    messages_db.append({'username': username, 'message': message})
    
    return redirect('/')

@app.route('/')
def index():
    # Template to display the messages
    template = '''
    <h1>Messages</h1>
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    <ul>
    {% for message in messages %}
        <li>{{ message.username }} says: {{ message.message }}</li>
    {% endfor %}
    </ul>
    '''
    
    return render_template_string(template, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)