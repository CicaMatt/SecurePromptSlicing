from flask import Flask, request, redirect, url_for

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Placeholder function for inserting messages into a database.
    # Replace this with actual database insertion logic.
    print(f"Inserting {username}: '{message}' into the database.")

@app.route('/', methods=['GET', 'POST'])
def main():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect(url_for('main'))
    
    # Render a simple form for the main page
    form_html = '''
    <form method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return form_html

if __name__ == '__main__':
    app.run(debug=True)