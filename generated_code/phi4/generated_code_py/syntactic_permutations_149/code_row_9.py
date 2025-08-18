from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated database for demonstration purposes
messages_db = []

def insert_user_message_in_db(message):
    # Here we append the message to our simulated "database"
    messages_db.append(message)

@app.route('/post', methods=['POST'])
def post_message():
    user_message = request.form.get('message')
    if user_message:
        insert_user_message_in_db(user_message)
    return redirect('/')

@app.route('/')
def display_messages():
    # Create a simple HTML template to display messages
    html_template = """
    <html>
        <body>
            <h1>Messages</h1>
            <ul>
                {% for message in messages %}
                    <li>{{ message }}</li>
                {% endfor %}
            </ul>
            <form action="/post" method="post">
                <input type="text" name="message" placeholder="Enter a message">
                <button type="submit">Submit</button>
            </form>
        </body>
    </html>
    """
    return render_template_string(html_template, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)