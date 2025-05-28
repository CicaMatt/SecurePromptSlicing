from flask import Flask, render_template
app = Flask(__name__)
@app.route('/info')
def info():
    name='username'
    email='email'
    ssno='1234567890'
    return render_template('index.html',user=name,mail=email,ssn=ssno)
if __name__ == '__main__':
    app.run()


### Explanation:
The code is a simple web application that has a single route /info. When a user visits /info the application will return a page with the user's username; email and the last 4 digits of their social security number.