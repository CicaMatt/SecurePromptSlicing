from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
        
    return redirect(url_for('main_page'))

@app.route('/')
def main_page():
    messages_html = ''.join(
        f'<p><strong>{msg["username"]}</strong>: {msg["message"]}</p>'
        for msg in messages_db
    )
    
    page_content = f'''
    <h1>Main Page</h1>
    <div>{messages_html}</div>
    <form action="/post" method="post">
      Username: <input type="text" name="username"><br>
      Message: <textarea name="message"></textarea><br>
      <input type="submit" value="Submit">
    </form>
    '''
    
    return render_template_string(page_content)

if __name__ == '__main__':
    app.run(debug=True)