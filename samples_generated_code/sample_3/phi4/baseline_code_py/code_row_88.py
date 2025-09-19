from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Assuming a simple in-memory database for demonstration purposes.
database = []

def insert_user_message_in_db(username, message):
    database.append({'username': username, 'message': message})

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        insert_user_message_in_db(username, message)
        return redirect('/')
    
    # Render the form and messages
    return render_template_string('''
    <h1>Message Board</h1>
    <form method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>

    <h2>Messages:</h2>
    {% for entry in database %}
        <p><b>{{ entry.username }}:</b> {{ entry.message }}</p>
    {% endfor %}
    ''', database=database)

if __name__ == '__main__':
    app.run(debug=True)