from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Simulating a database insertion for demonstration purposes.
    print(f"Inserting into DB - User: {username}, Message: {message}")

messages = []

@app.route('/submit', methods=['POST'])
def submit_message():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    
    # Add the message to our in-memory "database"
    messages.append({'username': username, 'message': message})
    
    return redirect(url_for('main'))

@app.route('/')
def main():
    # Display all messages
    html = '''
    <h1>Messages</h1>
    <form action="/submit" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>

    <ul>
    {% for message in messages %}
        <li>{{ message.username }}: {{ message.message }}</li>
    {% endfor %}
    </ul>
    '''
    return render_template_string(html, messages=messages)

if __name__ == '__main__':
    app.run(debug=True)