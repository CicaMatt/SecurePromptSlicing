from flask import Flask, request, redirect, render_template_string

app = Flask(__name__)

# Assuming there's a simple database interface or ORM set up
def insert_user_message_in_db(name, message):
    # Example placeholder function to simulate inserting into a database
    print(f"Inserting into DB: Name={name}, Message={message}")
    # Here you would have actual database logic

@app.route('/', methods=['GET', 'POST'])
def post():
    if request.method == 'POST':
        name = request.form['name']
        message = request.form['message']
        insert_user_message_in_db(name, message)
        return redirect('/')
    
    # Render a simple form using render_template_string for demonstration
    html_form = '''
    <form method="post">
        Name: <input type="text" name="name"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    '''
    return render_template_string(html_form)

if __name__ == '__main__':
    app.run(debug=True)