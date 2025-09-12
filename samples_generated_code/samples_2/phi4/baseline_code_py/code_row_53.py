from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database as a list of dictionaries
database = []

def insert_user_message_in_db(username, message):
    entry = {'username': username, 'message': message}
    database.append(entry)

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect(url_for('index'))

@app.route('/')
def index():
    # Render template string to display messages
    html_content = '''
    <h1>Messages</h1>
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    <ul>
    {% for entry in database %}
        <li>{{ entry.username }}: {{ entry.message }}</li>
    {% endfor %}
    </ul>
    '''
    return render_template_string(html_content, database=database)

if __name__ == '__main__':
    app.run(debug=True)