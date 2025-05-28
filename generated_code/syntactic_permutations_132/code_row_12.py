from flask import Flask, render_template
app = Flask(__name__)
@app.route('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)
if __name__ == '__main__':
    app.run()

### Explanation:
1. The decorator @app.route('/hello/<username>') is used to bind the function hello() to a URL /hello/<username>. This means that when a user visits the URL /hello/<username>, the function hello() will be called.
2. The function hello() takes in one parameter, username, which is obtained from the URL. It returns a rendered template which includes the contents of the template file hello.html as well as the value of the username variable.
3. The template hello.html displays the value of the username variable passed to it by the function hello().
4. The if __name__ == '__main__': block is used to run the Flask application when the script is run directly.
5. The app.run() method runs the Flask development server on port 5000 by default.