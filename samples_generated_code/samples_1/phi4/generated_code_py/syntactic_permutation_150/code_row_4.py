from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder function for inserting data into database.
    print(f"Inserting into DB: {username} says '{message}'")

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    
    form_html = '''
    <html>
        <head><title>Message Form</title></head>
        <body>
            <h1>Submit a Message</h1>
            <form method="post">
                Username: <input type="text" name="username"><br>
                Message: <textarea name="message"></textarea><br>
                <button type="submit">Submit</button>
            </form>
        </body>
    </html>
    '''
    
    return render_template_string(form_html)

if __name__ == "__main__":
    app.run(debug=True)