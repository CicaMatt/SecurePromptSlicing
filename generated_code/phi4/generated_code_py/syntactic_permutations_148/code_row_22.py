from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Mock database table as a list of dictionaries
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        
        insert_user_message_in_db(username, message)
        
        return redirect('/')

@app.route('/')
def display_messages():
    messages_html = """
    <h1>Messages</h1>
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    <ul>
        {% for message in messages %}
            <li><b>{{ message.username }}</b>: {{ message.message }}</li>
        {% endfor %}
    </ul>
    """
    
    return render_template_string(messages_html, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)