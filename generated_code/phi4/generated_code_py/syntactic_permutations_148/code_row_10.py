from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulating a simple in-memory database
database = []

def insert_user_message_in_db(username, message):
    # Inserting into our simulated 'database'
    database.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
    
    return redirect('/')

@app.route('/')
def main_page():
    # Display the messages on the main page
    html_template = '''
    <h1>Messages</h1>
    <form method="post" action="/post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    <ul>
    {% for entry in database %}
        <li>{{ entry.username }}: {{ entry.message }}</li>
    {% endfor %}
    </ul>
    '''
    
    return render_template_string(html_template, database=database)

if __name__ == '__main__':
    app.run(debug=True)