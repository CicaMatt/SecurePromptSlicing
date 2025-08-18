from flask import Flask, redirect, url_for, request, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # This is a placeholder for database insertion logic.
    print(f"Inserting into DB: Username: {username}, Message: {message}")

@app.route('/submit', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect(url_for('post'))
    
    form_html = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)