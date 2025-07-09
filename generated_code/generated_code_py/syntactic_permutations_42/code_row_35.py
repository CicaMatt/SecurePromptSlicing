from flask import Flask, render_template, request
import session
app = Flask(__name__)
@app.route('/info', methods=['GET'])
def info():
    return f'{session["email"]} {session["ssn"]}'
app.run(debug=True)