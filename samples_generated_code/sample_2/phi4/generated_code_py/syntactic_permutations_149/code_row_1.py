from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated database
messages_db = []

def insert_user_message_in_db(message):
    messages_db.append(message)

@app.route('/post', methods=['POST'])
def post_message():
    message = request.form.get('message')
    if message:
        insert_user_message_in_db(message)
    return redirect('/')

@app.route('/')
def display_messages():
    html_content = """
    <h1>Messages</h1>
    <form action="/post" method="post">
        <input type="text" name="message" placeholder="Enter your message here"/>
        <button type="submit">Send</button>
    </form>
    <ul>
    {% for message in messages %}
        <li>{{ message }}</li>
    {% endfor %}
    </ul>
    """
    return render_template_string(html_content, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)