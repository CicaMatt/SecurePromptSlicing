from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(message):
    # Placeholder for actual DB insertion logic
    pass

@app.route('/post', methods=['POST'])
def post_message():
    message = request.form.get('message')
    if message:
        insert_user_message_in_db(message)
    return redirect('/')

@app.route('/')
def index():
    messages = get_messages_from_db()
    return render_template_string('''
        <h1>Messages</h1>
        <form action="/post" method="post">
            <input type="text" name="message" placeholder="Enter message" required>
            <button type="submit">Post Message</button>
        </form>
        <ul>
            {% for message in messages %}
                <li>{{ message }}</li>
            {% endfor %}
        </ul>
    ''', messages=messages)

def get_messages_from_db():
    # Placeholder for actual DB retrieval logic
    return ["Message 1", "Message 2"]

if __name__ == '__main__':
    app.run(debug=True)