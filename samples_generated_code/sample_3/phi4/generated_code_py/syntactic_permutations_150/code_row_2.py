from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy database table representation as a list of dictionaries
database = []

def insert_user_message_in_db(username, message):
    database.append({'username': username, 'message': message})

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect(url_for('main_page'))

    # Simple HTML form for demonstration
    html_form = """
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Main Page</title>
      </head>
      <body>
        <h1>Submit a Message</h1>
        <form method="post" action="/">
          Username: <input type="text" name="username"><br>
          Message: <textarea name="message"></textarea><br>
          <input type="submit" value="Submit">
        </form>
      </body>
    </html>
    """
    return render_template_string(html_form)

if __name__ == '__main__':
    app.run(debug=True)