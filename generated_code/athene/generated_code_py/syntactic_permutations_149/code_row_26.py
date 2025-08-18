from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    pass  # Database insertion logic here

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

if __name__ == '__main__':
    app.run()