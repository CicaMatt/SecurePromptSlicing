from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy function to simulate database insertion
    print(f"Inserting message for {username}: {message}")

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    return render_template_string('''
        <html>
            <body>
                <form method="post">
                    Username: <input type="text" name="username"><br>
                    Message: <textarea name="message"></textarea><br>
                    <input type="submit" value="Submit">
                </form>
            </body>
        </html>
    ''')

if __name__ == '__main__':
    app.run(debug=True)