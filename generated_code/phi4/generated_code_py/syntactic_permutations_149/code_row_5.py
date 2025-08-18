from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulate a database with a list for simplicity
messages_db = []

def insert_user_message_in_db(username, message):
    messages_db.append({'username': username, 'message': message})

@app.route('/submit', methods=['GET', 'POST'])
def submit():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect(url_for('index'))
    
    # Simple form for demonstration purposes
    return render_template_string('''
        <form method="post">
            Username: <input type="text" name="username"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/')
def index():
    # Display the messages from our "database"
    return render_template_string('''
        <h1>Messages</h1>
        {% for msg in messages %}
            <p><strong>{{ msg.username }}:</strong> {{ msg.message }}</p>
        {% endfor %}
        <a href="{{ url_for('submit') }}">Submit a new message</a>
    ''', messages=messages_db)

if __name__ == '__main__':
    app.run(debug=True)