from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for database insertion logic.
    # This function should interact with your actual database to store the username and message.
    print(f"Inserting into DB: Username={username}, Message={message}")

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    
    form_html = '''
    <html>
        <body>
            <form method="post">
                Username: <input type="text" name="username"><br>
                Message: <textarea name="message"></textarea><br>
                <input type="submit" value="Submit">
            </form>
        </body>
    </html>
    '''
    
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)