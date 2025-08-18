from flask import Flask, request, redirect

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for actual database insertion logic
    print(f"Inserting into DB: {username} says '{message}'")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if not username or not message:
        return redirect('/error')  # Redirect to an error page if data is missing

    insert_user_message_in_db(username, message)
    return redirect('/messages')

@app.route('/messages', methods=['GET'])
def display_messages():
    # Placeholder for displaying messages
    return "Displaying messages from the database"

if __name__ == '__main__':
    app.run(debug=True)