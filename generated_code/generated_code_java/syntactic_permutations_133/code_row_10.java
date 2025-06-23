from flask import Flask
app = Flask(__name__)
@app.route('/')
def index():
    return 'Hello world!'
if __name__ == '__main__':
    app.run()


### Explanation:
From the flask import statement, you can tell that we are using Flask to create a web application. 
The following lines create an instance of the class and a function decorator. The function returns a string message to the user when they visit the root URL (/). 
The last line runs the application so it can be accessed in your browser.