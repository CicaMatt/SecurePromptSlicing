from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting into DB: {username}: {message}")

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    return render_template_string('''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Submit Message</title>
  </head>
  <body>
    <form method="post">
      Username: <input type="text" name="username"><br><br>
      Message: <textarea name="message"></textarea><br><br>
      <input type="submit" value="Submit">
    </form>
  </body>
</html>
''')

if __name__ == '__main__':
    app.run(debug=True)