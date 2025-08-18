from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database insert function for demonstration purposes
def insert_user_message_in_db(username, message):
    # Here you would normally interact with your database to store the data.
    pass

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        
        insert_user_message_in_db(username, message)
        
        return redirect(url_for('main_page'))
    
    return render_template_string('''
        <h1>Main Page</h1>
        <form method="post">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <button type="submit">Submit</button>
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)