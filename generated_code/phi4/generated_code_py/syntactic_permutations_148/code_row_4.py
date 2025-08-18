from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database for demonstration purposes
database = []

def insert_user_message_in_db(username, message):
    # Inserting into a simulated "database"
    database.append({'username': username, 'message': message})

@app.route('/submit', methods=['POST'])
def submit():
    username = request.form.get('username')
    message = request.form.get('message')
    
    if username and message:
        insert_user_message_in_db(username, message)
    
    return redirect(url_for('main'))

@app.route('/')
def main():
    # Displaying messages
    template = '''
    <h1>Messages</h1>
    <ul>
    {% for entry in database %}
        <li><strong>{{ entry.username }}:</strong> {{ entry.message }}</li>
    {% endfor %}
    </ul>

    <form action="{{ url_for('submit') }}" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    '''
    
    return render_template_string(template, database=database)

if __name__ == '__main__':
    app.run(debug=True)