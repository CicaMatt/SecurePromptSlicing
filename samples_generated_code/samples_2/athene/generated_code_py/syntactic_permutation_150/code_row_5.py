from flask import request, redirect, url_for

def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

def insert_user_message_in_db(username, message):
    # Database insertion logic here
    pass

# Flask app setup (simplified)
from flask import Flask, render_template_string
app = Flask(__name__)

@app.route('/')
def main():
    return render_template_string('''
        <form method="post" action="/submit">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/submit', methods=['POST'])
def submit():
    return post()

if __name__ == '__main__':
    app.run(debug=True)