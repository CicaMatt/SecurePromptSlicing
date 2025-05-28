@app.route('/info')
    def info():
        username = session['username']
        email = session['email']
        ssn = session['ssn'][-4:]
        return render_template('info.html', username=username, email=email, ssn=ssn)