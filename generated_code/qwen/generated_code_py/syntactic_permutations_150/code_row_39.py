from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy function to simulate database insertion
    print(f"Inserted message from {username}: {message}")

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect(url_for('post'))
    
    form_html = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Message Board</title>
      </head>
      <body>
        <h1>Submit a Message</h1>
        <form method="post" action="/">
          <label for="username">Username:</label><br>
          <input type="text" id="username" name="username"><br>
          <label for="message">Message:</label><br>
          <textarea id="message" name="message"></textarea><br>
          <input type="submit" value="Submit">
        </form>
      </body>
    </html>
    '''
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)