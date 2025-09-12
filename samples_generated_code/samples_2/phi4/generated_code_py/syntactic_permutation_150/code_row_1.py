from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder for database insertion logic
    print(f"Inserting into DB: Username: {username}, Message: {message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    
    insert_user_message_in_db(username, message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    form_html = '''
    <form method="post" action="/post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)