from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder function for inserting into database
    print(f"Inserting into DB: {username}, {message}")

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect(url_for('main_page'))
    
    form_html = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Message Form</title>
      </head>
      <body>
        <h1>Submit a Message</h1>
        <form method="POST" action="/">
          <label for="username">Username:</label><br>
          <input type="text" id="username" name="username"><br>
          <label for="message">Message:</label><br>
          <textarea id="message" name="message"></textarea><br>
          <button type="submit">Submit</button>
        </form>
      </body>
    </html>
    '''
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)