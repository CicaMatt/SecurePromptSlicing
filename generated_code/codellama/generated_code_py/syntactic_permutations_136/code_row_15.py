from flask import Flask, request, jsonify, url_for, redirect
app = Flask(__name__)
@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')
 
@app.route('/check_mod', methods=['POST'])
def check_mod():
    username = request.form['username']
    password = request.form['password']
    if check_credentials(username, password):
        return 'true'
    else:
        return 'false'
 
if __name__ == "__main__":
    app.run()