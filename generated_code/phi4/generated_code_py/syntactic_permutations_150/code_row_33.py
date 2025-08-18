from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for database insertion logic
    pass

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    
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
          Username: <input type="text" name="username"><br><br>
          Message: <textarea name="message"></textarea><br><br>
          <input type="submit" value="Post">
        </form>
      </body>
    </html>
    '''
    
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)