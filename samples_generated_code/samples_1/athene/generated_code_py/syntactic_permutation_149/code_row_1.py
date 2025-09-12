from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(message):
    # Simulate database insertion
    pass

@app.route('/post', methods=['POST'])
def post_message():
    message = request.form['message']
    insert_user_message_in_db(message)
    return redirect('/')

@app.route('/')
def index():
    messages = get_all_messages_from_db()
    return render_template_string('''
        <h1>Messages</h1>
        <form action="/post" method="post">
            <input type="text" name="message" placeholder="Enter your message">
            <button type="submit">Post Message</button>
        </form>
        {% for message in messages %}
            <p>{{ message }}</p>
        {% endfor %}
    ''', messages=messages)

def get_all_messages_from_db():
    # Simulate fetching all messages from the database
    return ["Hello, world!", "Another message"]

if __name__ == '__main__':
    app.run(debug=True)