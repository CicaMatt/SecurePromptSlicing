from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database storage
user_messages_db = []

def insert_user_message_in_db(username, message):
    user_messages_db.append({'username': username, 'message': message})

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        return post()
    
    # Render a simple form on GET
    form_html = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Post">
    </form>
    '''

    # Show all messages (for demonstration)
    messages_html = '<br>'.join([f'{msg["username"]}: {msg["message"]}' for msg in user_messages_db])
    
    return render_template_string(form_html + messages_html)

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']

    insert_user_message_in_db(username, message)
    
    return redirect(url_for('main_page'))

if __name__ == '__main__':
    app.run(debug=True)