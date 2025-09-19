from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulated database insert function
def insert_user_message_in_db(username, message):
    print(f"Inserting into DB: Username - {username}, Message - {message}")

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')

    # Simple form to submit a message
    html_form = """
    <html>
      <body>
        <h1>Submit your message</h1>
        <form method="post">
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