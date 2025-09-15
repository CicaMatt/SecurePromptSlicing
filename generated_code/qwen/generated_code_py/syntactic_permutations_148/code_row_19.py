from flask import Flask, request, redirect, render_template

app = Flask(__name__)

# Mock function to simulate database insertion
def insert_user_message_in_db(username, message):
    # Simulate inserting into a database
    print(f"Inserted message: {message} from user: {username}")

# Mock data to simulate fetched messages from the database
messages = []

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    # Add message to mock database
    messages.append((username, message))
    return redirect('/')

@app.route('/')
def index():
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




