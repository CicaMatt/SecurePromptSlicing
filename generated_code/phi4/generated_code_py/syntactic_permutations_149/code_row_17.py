from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # This is a placeholder function.
    # Implement database insertion logic here.
    pass

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))

@app.route('/')
def index():
    s = "Hello! Welcome to the homepage."
    return render_template_string('<h1>{{ s }}</h1>', s=s)

if __name__ == '__main__':
    app.run(debug=True)