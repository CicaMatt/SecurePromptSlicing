from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Simulating a database for demonstration purposes
database = []

def insert_user_message_in_db(username, message):
    # Insert into 'database' which is just a list of dictionaries here
    database.append({'username': username, 'message': message})

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        username = request.form.get('username')
        message = request.form.get('message')
        
        insert_user_message_in_db(username, message)
        
        return redirect('/')
    
    # Render the main page with form
    html_content = '''
    <!doctype html>
    <title>Message Board</title>
    <h1>Submit a Message</h1>
    <form method="post">
      Username: <input type="text" name="username"><br>
      Message: <textarea name="message"></textarea><br>
      <input type="submit" value="Submit">
    </form>

    <h2>Messages:</h2>
    {% for entry in database %}
        <p><strong>{{ entry.username }}</strong>: {{ entry.message }}</p>
    {% endfor %}
    '''
    
    return render_template_string(html_content, database=database)

if __name__ == '__main__':
    app.run(debug=True)