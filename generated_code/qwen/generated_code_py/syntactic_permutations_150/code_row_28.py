from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(name, message):
    # This is a placeholder for database insertion logic
    print(f"Name: {name}, Message: {message}")

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        name = request.form.get('name')
        message = request.form.get('message')
        insert_user_message_in_db(name, message)
        return redirect('/')
    
    form_html = '''
    <form method="post">
        Name: <input type="text" name="name"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)