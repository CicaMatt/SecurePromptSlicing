from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(name, message):
    # Placeholder for database insertion logic.
    print(f"Inserting into DB: Name={name}, Message={message}")

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        name = request.form.get('name')
        message = request.form.get('message')
        insert_user_message_in_db(name, message)
        return redirect(url_for('main_page'))
    
    form_html = '''
    <form method="post">
        Name: <input type="text" name="name"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return form_html

if __name__ == '__main__':
    app.run(debug=True)