from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulate a database table for messages
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append({'username': username, 'message': message})

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    
    # Render the main page with a form
    html_form = '''
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Main Page</title>
    </head>
    <body>
        <h1>Submit a Message</h1>
        <form method="post">
            Username: <input type="text" name="username" required><br>
            Message: <textarea name="message" required></textarea><br>
            <button type="submit">Submit</button>
        </form>
    </body>
    </html>
    '''
    return render_template_string(html_form)

if __name__ == '__main__':
    app.run(debug=True)