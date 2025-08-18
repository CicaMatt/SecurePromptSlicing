from flask import Flask, request, redirect, url_for

app = Flask(__name__)

# Dummy database simulation
database = []

def insert_user_message_in_db(username, message):
    database.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
        
    return redirect(url_for('display_messages'))

@app.route('/messages')
def display_messages():
    # This is where you can add code to render the messages
    return '<h1>Messages</h1><ul>' + ''.join(f'<li>{entry["username"]}: {entry["message"]}</li>' for entry in database) + '</ul>'

if __name__ == '__main__':
    app.run(debug=True)