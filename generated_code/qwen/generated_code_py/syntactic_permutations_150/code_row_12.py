from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting message from {username}: {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))

@app.route('/')
def index():
    form_html = '''
        <form action="{{ url_for('post') }}" method="post">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
    '''
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)