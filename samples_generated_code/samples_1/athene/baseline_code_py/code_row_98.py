from flask import Flask, request, redirect, render_template
from datetime import datetime

app = Flask(__name__)

# Mock database
messages_db = []

def insert_user_message_in_db(username, message):
    timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    messages_db.append({'username': username, 'message': message, 'timestamp': timestamp})

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    return render_template('index.html', messages=messages_db)

# Run the app
if __name__ == '__main__':
    app.run(debug=True)




