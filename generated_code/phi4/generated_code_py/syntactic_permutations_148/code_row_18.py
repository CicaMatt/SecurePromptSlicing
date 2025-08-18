from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database as a list
messages_db = []

def insert_user_message_in_db(message):
    messages_db.append(message)

@app.route('/post', methods=['POST'])
def post():
    message = request.form.get('message')
    if message:
        insert_user_message_in_db(message)
    return redirect(url_for('main_page'))

@app.route('/')
def main_page():
    html_content = """
    <html>
      <body>
        <h1>Messages</h1>
        <form method="post" action="/post">
          <input type="text" name="message" placeholder="Enter your message here"/>
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