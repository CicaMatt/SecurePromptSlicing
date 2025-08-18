from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for database insertion logic
    pass

@app.route('/submit', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
    
    return redirect(url_for('main_page'))

@app.route('/')
def main_page():
    # Placeholder for the main page content
    return "Main Page"

if __name__ == '__main__':
    app.run(debug=True)