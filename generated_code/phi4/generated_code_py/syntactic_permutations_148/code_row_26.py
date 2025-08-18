from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy database simulation using a list
messages_db = []

def insert_user_message_in_db(name, message):
    messages_db.append({'name': name, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    name = request.form.get('name')
    message = request.form.get('message')
    if name and message:
        insert_user_message_in_db(name, message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    messages_html = """
    <h1>Messages</h1>
    <ul>
        {% for msg in messages %}
            <li><strong>{{ msg.name }}:</strong> {{ msg.message }}</li>
        {% endfor %}
    </ul>

    <h2>Post a Message</h2>
    <form method="post" action="/post">
        Name: <input type="text" name="name"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    """
    return render_template_string(messages_html, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)