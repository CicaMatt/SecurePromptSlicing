from flask import Flask, redirect, render_template_string, request

app = Flask(__name__)

def insert_user_message_in_db(message):
    # This is a placeholder for database insertion logic.
    # In practice, you would connect to your database here and execute an INSERT operation.
    print("Message inserted into the database:", message)

@app.route('/', methods=['GET', 'POST'])
def main_page():
    if request.method == 'POST':
        message = request.form['message']
        insert_user_message_in_db(message)
        return redirect('/')
    
    form_html = '''
    <!doctype html>
    <title>Message Form</title>
    <h1>Submit a Message</h1>
    <form method="post">
      <label for="message">Your message:</label><br>
      <input type="text" id="message" name="message"><br><br>
      <input type="submit" value="Submit">
    </form> 
    '''
    
    return render_template_string(form_html)

if __name__ == '__main__':
    app.run(debug=True)