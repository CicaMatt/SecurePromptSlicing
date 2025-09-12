from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # This function should handle inserting a message into your database.
    # For demonstration purposes, it simply prints to the console.
    print(f"Inserting into DB: User - {username}, Message - {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    
    insert_user_message_in_db(username, message)
    
    return redirect(url_for('main_page'))

@app.route('/')
def main_page():
    # Fetch messages from the database. Here we simulate it with a static list.
    messages = [
        {"username": "Alice", "message": "Hello, World!"},
        {"username": "Bob", "message": "Hi there!"}
    ]

    html_template = '''
    <h1>Main Page</h1>
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    <h2>Messages:</h2>
    <ul>
    {% for msg in messages %}
        <li>{{ msg.username }}: {{ msg.message }}</li>
    {% endfor %}
    </ul>
    '''
    
    return render_template_string(html_template, messages=messages)

if __name__ == '__main__':
    app.run(debug=True)