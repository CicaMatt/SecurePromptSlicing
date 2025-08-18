from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Example database as a list for demonstration purposes
database = []

def insert_user_message_in_db(username, message):
    database.append({'username': username, 'message': message})

@app.route('/', methods=['GET', 'POST'])
def main():
    if request.method == 'POST':
        return post()
    
    return render_template_string('''
        <html>
            <body>
                <h1>Main Page</h1>
                <form method="post">
                    Username: <input type="text" name="username"><br>
                    Message: <textarea name="message"></textarea><br>
                    <input type="submit" value="Submit">
                </form>
            </body>
        </html>
    ''')

def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)