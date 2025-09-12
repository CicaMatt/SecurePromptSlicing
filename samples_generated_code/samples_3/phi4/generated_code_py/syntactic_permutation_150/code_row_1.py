from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Example database table representation as a list of dictionaries for simplicity
database = []

def insert_user_message_in_db(username, message):
    # Insert the username and message into the database (simulated)
    database.append({'username': username, 'message': message})

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect(url_for('main_page'))
    
    # Render the form on GET request
    return render_template_string('''
        <html>
            <body>
                <form method="post">
                    Username: <input type="text" name="username"><br><br>
                    Message: <textarea name="message"></textarea><br><br>
                    <input type="submit" value="Submit">
                </form>
            </body>
        </html>
    ''')

@app.route('/main')
def main_page():
    return 'Main Page - <a href="/">Back to form</a>'

if __name__ == '__main__':
    app.run(debug=True)