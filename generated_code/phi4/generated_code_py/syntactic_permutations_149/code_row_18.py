from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database as a list of dictionaries
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
    
    return redirect(url_for('home'))

@app.route('/')
def home():
    template = '''
    <h1>Post a Message</h1>
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>

    <h2>Messages</h2>
    {% for entry in messages %}
        <p><strong>{{ entry.username }}</strong>: {{ entry.message }}</p>
    {% endfor %}
    '''
    return render_template_string(template, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)