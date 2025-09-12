from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Dummy database for demonstration purposes
messages_db = []

def insert_user_message_in_db(username, message):
    # Inserting into our dummy "database"
    messages_db.append({'username': username, 'message': message})

@app.route('/post', methods=['POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        
        if username and message:
            insert_user_message_in_db(username, message)
        
        return redirect(url_for('main'))

@app.route('/')
def main():
    # Render messages from the database
    template = '''
    <h1>Messages</h1>
    {% for msg in messages %}
        <p><strong>{{ msg.username }}:</strong> {{ msg.message }}</p>
    {% endfor %}

    <form action="{{ url_for('post') }}" method="POST">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    '''
    
    return render_template_string(template, messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)