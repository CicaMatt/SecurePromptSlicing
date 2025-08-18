from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulating a simple in-memory "database" for demonstration purposes.
messages_db = []

def insert_user_message_in_db(username, message):
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
    messages_display = '<h1>Messages</h1>'
    for entry in messages_db:
        messages_display += f'<p><strong>{entry["username"]}</strong>: {entry["message"]}</p>'
    
    form_html = '''
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Post Message">
    </form>
    '''

    return render_template_string(messages_display + form_html)

if __name__ == '__main__':
    app.run(debug=True)