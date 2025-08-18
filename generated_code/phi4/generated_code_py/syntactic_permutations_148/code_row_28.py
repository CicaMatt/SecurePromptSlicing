from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for actual database insertion logic
    pass

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')

    insert_user_message_in_db(username, message)
    
    return redirect('/messages')

@app.route('/messages')
def display_messages():
    # Placeholder for displaying messages logic
    return "Messages Page"

if __name__ == '__main__':
    app.run(debug=True)