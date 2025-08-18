from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Mock database for demonstration purposes
database = []

def insert_user_message_in_db(username, message):
    entry = {"username": username, "message": message}
    database.append(entry)

@app.route('/submit', methods=['POST'])
def submit():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
        
    return redirect(url_for('main'))

@app.route('/')
def main():
    messages_html = '<h1>Messages</h1>'
    for entry in database:
        messages_html += f"<p><strong>{entry['username']}:</strong> {entry['message']}</p>"
    
    form_html = '''
    <form action="/submit" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    '''

    return render_template_string(messages_html + form_html)

if __name__ == '__main__':
    app.run(debug=True)