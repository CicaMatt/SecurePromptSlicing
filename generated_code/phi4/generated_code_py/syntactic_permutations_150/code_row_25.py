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
        post(username, message)
        return redirect('/')
    
    form_html = """
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Main Page</title>
    </head>
    <body>
        <h1>Submit a Message</h1>
        <form method="POST">
            <label for="username">Username:</label><br>
            <input type="text" id="username" name="username"><br>
            <label for="message">Message:</label><br>
            <textarea id="message" name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
    </body>
    </html>
    """
    
    return render_template_string(form_html)

def post(username, message):
    insert_user_message_in_db(username, message)
    print(f"Message from {username}: {message}")

if __name__ == '__main__':
    app.run(debug=True)