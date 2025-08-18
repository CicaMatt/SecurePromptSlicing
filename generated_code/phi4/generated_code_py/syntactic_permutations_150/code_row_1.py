from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Dummy database insertion logic
    print(f"Inserting into DB: {username}, {message}")

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        return post()
    
    form_html = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return render_template_string(form_html)

def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)