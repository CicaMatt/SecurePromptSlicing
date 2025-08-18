from flask import Flask, request, redirect, url_for, render_template_string

app = Flask(__name__)

# Simulated database
database = []

def insert_user_message_in_db(name, message):
    """Inserts a user message into the simulated database."""
    entry = {'name': name, 'message': message}
    database.append(entry)

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        name = request.form.get('name')
        message = request.form.get('message')
        insert_user_message_in_db(name, message)
        return redirect(url_for('main_page'))
    
    # Render form for GET requests
    return render_template_string('''
        <form method="post">
            Name: <input type="text" name="name"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
    ''')

@app.route('/main')
def main_page():
    messages = database
    return render_template_string('''
        <h1>Main Page</h1>
        {% for entry in messages %}
            <p><strong>{{ entry.name }}</strong>: {{ entry.message }}</p>
        {% endfor %}
        
        <a href="{{ url_for('post') }}">Submit a new message</a>
    ''', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)