from flask import Flask, redirect, url_for
app = Flask(__name__)
@app.route('/')
def index():
    return render_template('index.html')

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))

### Explanation:

- The Flask module is imported and the app variable is set to a new instance of the Flask class.
- The index() function will be called when the user goes to the root URL of our application. It returns a page that includes a form for the user to enter their name and message.
- The post() function will be called when the user submits the form. It retrieves the username and message from the request, calls insert_user_message_in_db() with those values, and then redirects the user back to the main page.
- The render_template() function is used to generate the HTML for the index page. This function will look for a file called index.html in the templates directory of our application. We haven't created that file yet, but we will do so next.