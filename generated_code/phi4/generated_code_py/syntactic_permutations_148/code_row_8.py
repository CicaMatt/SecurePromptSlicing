from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Placeholder for a database connection; replace with actual database logic.
def insert_user_message_in_db(username, message):
    # This function should contain logic to insert username and message into the database.
    print(f"Inserting into DB - Username: {username}, Message: {message}")

@app.route('/submit', methods=['POST'])
def submit_message():
    username = request.form.get('username')
    message = request.form.get('message')
    if username and message:
        insert_user_message_in_db(username, message)
    return redirect(url_for('main_page'))

@app.route('/')
def main_page():
    # Placeholder messages; replace with actual database retrieval logic.
    messages = [
        {'username': 'Alice', 'message': 'Hello World!'},
        {'username': 'Bob', 'message': 'Hi there!'}
    ]
    
    html_content = '''
    <h1>Messages</h1>
    <form action="/submit" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <button type="submit">Submit</button>
    </form>
    <ul>
        {% for message in messages %}
            <li><strong>{{ message.username }}:</strong> {{ message.message }}</li>
        {% endfor %}
    </ul>
    '''
    
    return render_template_string(html_content, messages=messages)

if __name__ == '__main__':
    app.run(debug=True)