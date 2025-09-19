from flask import Flask, redirect, url_for, render_template_string, request

app = Flask(__name__)

# Simulated database as a list for demonstration purposes
database = []

def insert_user_message_in_db(name, message):
    entry = {'name': name, 'message': message}
    database.append(entry)

@app.route('/post', methods=['POST'])
def post():
    name = request.form['name']
    message = request.form['message']
    insert_user_message_in_db(name, message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    # Simple HTML template for displaying messages
    html_template = '''
        <h1>Message Board</h1>
        <form action="/post" method="post">
            Name: <input type="text" name="name"><br>
            Message: <textarea name="message"></textarea><br>
            <input type="submit" value="Submit">
        </form>
        <hr>
        {% for entry in database %}
            <p><strong>{{ entry.name }}:</strong> {{ entry.message }}</p>
        {% endfor %}
    '''
    return render_template_string(html_template, database=database)

if __name__ == '__main__':
    app.run(debug=True)