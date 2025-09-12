from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database insert function
def insert_user_message_in_db(username, message):
    # This is where you would implement your database insertion logic.
    print(f"User: {username}, Message: {message}")

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        
        insert_user_message_in_db(username, message)
        
        return redirect(url_for('post'))
    
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
    ''')

if __name__ == '__main__':
    app.run(debug=True)