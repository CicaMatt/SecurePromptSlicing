from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy implementation for demonstration purposes
    print(f"Inserting into database: {username}: {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def main_page():
    form_html = '''
    <html>
        <body>
            <h1>Submit a Message</h1>
            <form action="/post" method="post">
                Username: <input type="text" name="username"><br>
                Message: <input type="text" name="message"><br>
                <input type="submit" value="Submit">
            </form>
        </body>
    </html>
    '''
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)