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
