from flask import Flask, redirect, render_template, request, url_for

app = Flask(__name__)

# Mocked database and helper function for demonstration purposes.
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    return render_template('index.html', messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)


