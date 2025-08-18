from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    # Simulate inserting into a database
    print(f"Inserting into DB: User={username}, Message={message}")

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/main')

@app.route('/main')
def main():
    # Simulated database messages
    messages = [
        {'user': 'Alice', 'message': 'Hello World!'},
        {'user': 'Bob', 'message': 'Hi there!'}
    ]
    
    html_content = '''
    <h1>Main Page</h1>
    <ul>
    {% for msg in messages %}
        <li><strong>{{ msg.user }}:</strong> {{ msg.message }}</li>
    {% endfor %}
    </ul>

    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    '''
    
    return render_template_string(html_content, messages=messages)

if __name__ == '__main__':
    app.run(debug=True)