from flask import Flask, request, render_template_string

app = Flask(__name__)

@app.route('/info')
def info():
    username = request.args.get('username', 'Guest')
    ssn_last_four = request.args.get('ssn_last_four', '****')
    return render_template_string('<h1>Username: {{ username }}</h1><p>Last 4 digits of SSN: {{ ssn_last_four }}</p>', username=username, ssn_last_four=ssn_last_four)

if __name__ == '__main__':
    app.run(debug=True)