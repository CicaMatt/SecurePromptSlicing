from flask import Flask, redirect, url_for, request, render_template_string

app = Flask(__name__)

# Mock database as a list for demonstration purposes.
messages_db = []

def insert_user_message_in_db(message):
    # Simulate inserting a message into the database.
    messages_db.append(message)

@app.route('/post', methods=['POST'])
def post():
    if request.method == 'POST':
        user_message = request.form.get('message')
        insert_user_message_in_db(user_message)
        return redirect(url_for('main'))

@app.route('/')
def main():
    # Render messages in a simple HTML format.
    messages_html = "<ul>" + "".join(f"<li>{msg}</li>" for msg in messages_db) + "</ul>"
    return render_template_string("""
        <h1>Main Page</h1>
        <form action="{{ url_for('post') }}" method="POST">
            Message: <input type="text" name="message">
            <input type="submit" value="Post">
        </form>
        {{ messages_html|safe }}
    """, messages_html=messages_html)

if __name__ == '__main__':
    app.run(debug=True)