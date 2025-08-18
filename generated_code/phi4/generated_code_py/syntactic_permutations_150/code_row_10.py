from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Simulate database insertion (replace with actual DB logic)
    print(f"Inserting into DB: Username={username}, Message={message}")

@app.route('/', methods=['GET', 'POST'])
def submit_message():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect(url_for('main_page'))
    
    # Render main page with form
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/main')
def main_page():
    return "Main Page"

if __name__ == '__main__':
    app.run(debug=True)