from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # This is a placeholder for actual database logic.
    print(f"Inserting into DB: Username={username}, Message={message}")

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form.get('username')
    message = request.form.get('message')

    if not username or not message:
        return "Username and message are required", 400

    insert_user_message_in_db(username, message)
    
    # Redirect to a page to display messages (assuming /display exists for demonstration)
    return redirect(url_for('display_messages'))

@app.route('/display')
def display_messages():
    # This is just a placeholder. In practice, you'd fetch data from the database.
    sample_data = [
        {"username": "Alice", "message": "Hello World!"},
        {"username": "Bob", "message": "Flask is awesome!"}
    ]
    
    messages_html = """
    <h1>Messages</h1>
    <ul>
        {% for data in messages %}
            <li><strong>{{ data.username }}:</strong> {{ data.message }}</li>
        {% endfor %}
    </ul>
    """
    return render_template_string(messages_html, messages=sample_data)

if __name__ == '__main__':
    app.run(debug=True)