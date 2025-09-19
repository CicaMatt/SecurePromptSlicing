from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock database and functions for demonstration purposes
messages = []

def insert_user_message_in_db(message):
    messages.append(message)

@app.route('/post', methods=['POST'])
def post():
    message = request.form.get('message')
    if message:
        insert_user_message_in_db(message)
    return redirect('/')

@app.route('/')
def index():
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




