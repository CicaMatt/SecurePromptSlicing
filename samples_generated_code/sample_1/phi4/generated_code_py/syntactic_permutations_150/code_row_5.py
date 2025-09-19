from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append({'username': username, 'message': message})

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        return post()
    
    form_html = '''
    <form method="post" action="/">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>

    <h2>Messages</h2>
    <ul>
    {% for message in messages %}
        <li>{{ message.username }}: {{ message.message }}</li>
    {% endfor %}
    </ul>
    '''
    
    return render_template_string(form_html, messages=messages_db)

def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect(url_for('main_page'))

if __name__ == '__main__':
    app.run(debug=True)