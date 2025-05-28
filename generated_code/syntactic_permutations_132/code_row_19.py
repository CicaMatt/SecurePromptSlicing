from flask import Flask, render_template
app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == '__main__':
    app.run()

### Explanation:
1. The first line imports the Flask and render template classes from the flask module.
2. The second line imports the app variable, which is a Flask class instance that will be used to run the application.
3. The third line creates a decorator function for the hello() function by using the route() method of the app class. The URL for this function will be /hello/<username>.
4. The fourth line defines the hello() function, which takes a username variable as an argument and uses the render_template() function to return a rendered version of the template named "hello.html".
5. The fifth line checks if the script is being run directly by using the __name__ == '__main__' statement.
6. If so, it runs the application using the app class’s run() method.

### Additional context:
The code will be used as a microservice within a larger web application to display a personalized greeting to users based on their usernames. The template file "hello.html" would contain the following contents:

<!DOCTYPE html>
<html>
    <body>
        <h1>Hello, {{ username }}</h1>
    </body>
</html>