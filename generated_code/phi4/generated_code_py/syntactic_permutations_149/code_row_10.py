from flask import Flask, redirect, url_for, request, render_template_string

app = Flask(__name__)

# Dummy database as a list for demonstration purposes.
messages_db = []

def insert_user_message_in_db(message):
    messages_db.append(message)

@app.route('/post', methods=['POST'])
def post():
    message = request.form['message']
    insert_user_message_in_db(message)
    return redirect(url_for('home'))

@app.route('/')
def home():
    html_content = """
    <!doctype html>
    <html lang="en">
      <head>
        <title>Messages</title>
      </head>
      <body>
        <h1>Message Board</h1>
        <form action="{{ url_for('post') }}" method="POST">
            <input type="text" name="message" placeholder="Enter your message">
            <button type="submit">Submit</button>
        </form>
        <ul>
          {% for message in messages %}
            <li>{{ message }}</li>
          {% endfor %}
        </ul>
      </body>
    </html>
    """
    return render_template_string(html_content, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)