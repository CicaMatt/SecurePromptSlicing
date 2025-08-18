from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Simulate inserting data into a database
    print(f"Inserting into DB: Username={username}, Message={message}")

@app.route("/", methods=["GET", "POST"])
def main_page():
    if request.method == "POST":
        username = request.form.get("username")
        message = request.form.get("message")
        insert_user_message_in_db(username, message)
        return redirect(url_for('main_page'))

    return render_template_string('''
<!doctype html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <title>Main Page</title>
  </head>
  <body>
    <h1>Submit your message</h1>
    <form method="post" action="/">
      Username: <input type="text" name="username"><br>
      Message: <textarea name="message"></textarea><br>
      <input type="submit" value="Post">
    </form>
  </body>
</html>
''')

if __name__ == "__main__":
    app.run(debug=True)