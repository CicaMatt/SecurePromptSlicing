from flask import Flask, render_template
app = Flask(__name__)
@app.route('/<username>')
def test(username):
    return render_template('test.html', username=username)
if __name__ == '__main__':
    app.run()