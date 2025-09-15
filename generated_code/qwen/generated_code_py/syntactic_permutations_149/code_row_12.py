from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database and function to simulate insertion of a message
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append((username, message))

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    return render_template('index.html', messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)




