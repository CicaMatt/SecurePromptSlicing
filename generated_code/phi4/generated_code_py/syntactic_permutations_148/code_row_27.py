from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for actual database insertion logic.
    print(f"Inserting into DB: {username} - {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
        
    return redirect(url_for('display_messages'))

@app.route('/messages')
def display_messages():
    # Placeholder for logic to fetch and display messages from the database.
    return "Displaying messages..."

if __name__ == '__main__':
    app.run(debug=True)