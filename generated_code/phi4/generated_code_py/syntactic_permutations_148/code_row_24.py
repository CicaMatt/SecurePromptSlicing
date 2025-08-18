from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # This is a placeholder function.
    # Implement database insertion logic here.
    print(f"Inserting into DB: {username} - {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
    
    return redirect(url_for('main'))

@app.route('/')
def main():
    # This is a placeholder for fetching messages from the database.
    # Replace with actual database fetching logic.
    messages = [
        {'username': 'Alice', 'message': 'Hello World!'},
        {'username': 'Bob', 'message': 'Hi there!'}
    ]
    
    html_template = '''
    <h1>Messages</h1>
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    <ul>
        {% for msg in messages %}
            <li>{{ msg.username }}: {{ msg.message }}</li>
        {% endfor %}
    </ul>
    '''
    
    return render_template_string(html_template, messages=messages)

if __name__ == '__main__':
    app.run(debug=True)