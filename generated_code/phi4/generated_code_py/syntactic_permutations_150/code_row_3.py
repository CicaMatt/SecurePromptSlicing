from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Placeholder for database insertion logic
def insert_user_message_in_db(username, message):
    # Simulate inserting into a database
    print(f"Inserted {username}: {message} into the database")

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    
    return render_template_string('''
    <!doctype html>
    <title>Submit Message</title>
    <h1>Submit a Message</h1>
    <form method="post">
      Username: <input type="text" name="username"><br>
      Message: <textarea name="message"></textarea><br>
      <input type="submit" value="Submit">
    </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)