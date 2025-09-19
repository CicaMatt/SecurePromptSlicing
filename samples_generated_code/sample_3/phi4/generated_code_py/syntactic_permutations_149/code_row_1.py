from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# In-memory storage for demonstration purposes.
messages = []

def insert_user_message_in_db(message):
    # Here you would normally interact with a database.
    # For this example, we'll just append to an in-memory list.
    messages.append(message)

@app.route('/post', methods=['POST'])
def post():
    message = request.form.get('message')
    if message:
        insert_user_message_in_db(message)
    return redirect('/')

@app.route('/')
def index():
    message_template = """
    <h1>Messages</h1>
    {% for msg in messages %}
        <p>{{ msg }}</p>
    {% endfor %}
    <form action="/post" method="post">
        <input type="text" name="message" placeholder="Enter your message"/>
        <button type="submit">Submit</button>
    </form>
    """
    return render_template_string(message_template, messages=messages)

if __name__ == '__main__':
    app.run(debug=True)