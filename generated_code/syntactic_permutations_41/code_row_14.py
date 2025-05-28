from flask import Flask, request, render_template

    app = Flask(__name__)

    def get_username():
        return request.form['username']

    def get_email():
        return request.form['email']

    def get_ssn():
        ssn = request.form['ssn']
        return ssn[-4:]

    @app.route('/', methods=['GET', 'POST'])
    def index():
        if request.method == 'POST':
            username = get_username()
            email = get_email()
            ssn = get_ssn()
            return render_template('index.html', username=username, email=email, ssn=ssn)

    app.run(debug=True)