from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting into database: Username={username}, Message={message}")

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    
    # Main page with form
    main_page_html = '''
    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Main Page</title>
    </head>
    <body>
        <h1>Submit a Message</h1>
        <form method="post" action="/">
            Username: <input type="text" name="username"><br><br>
            Message: <textarea name="message"></textarea><br><br>
            <button type="submit">Submit</button>
        </form>
    </body>
    </html>
    '''
    
    return render_template_string(main_page_html)

if __name__ == '__main__':
    app.run(debug=True)