from flask import Flask, redirect, url_for, request, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(name, message):
    # This is just a placeholder function to simulate database insertion.
    print(f"Inserting into DB: Name - {name}, Message - {message}")

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        name = request.form.get('name')
        message = request.form.get('message')
        post(name, message)
        return redirect(url_for('main_page'))

    form_html = '''
    <form method="post">
        Name: <input type="text" name="name"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    '''

    return render_template_string(form_html)

def post(name, message):
    insert_user_message_in_db(name, message)
    # Redirect back to the main page
    return redirect(url_for('main_page'))

if __name__ == '__main__':
    app.run(debug=True)