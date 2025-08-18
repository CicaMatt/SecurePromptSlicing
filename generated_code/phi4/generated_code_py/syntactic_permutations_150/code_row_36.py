from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # This is a placeholder function.
    # Here you would implement database insertion logic.
    print(f"Inserting into DB: User - {username}, Message - {message}")

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        
        insert_user_message_in_db(username, message)
        
        return redirect('/')
    
    form_html = '''
    <!doctype html>
    <html lang="en">
      <head>
        <title>Submit a Message</title>
      </head>
      <body>
        <h1>Submit your message</h1>
        <form method="post">
          Username: <input type="text" name="username"><br><br>
          Message: <textarea name="message"></textarea><br><br>
          <input type="submit" value="Submit">
        </form>
      </body>
    </html>
    '''
    
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)