from flask import Flask,session,request,render_template,redirect,url_for,flash
    app = Flask(__name__)
    app.config['SECRET_KEY']='secretkey'

    @app.route('/info',methods=['GET'])
    def info():
        if 'username' in session:
            username=session['username']
            email=session['email']
            ssn=session['ssn']
            return render_template('page2.html',username=username,email=email,ssn=ssn)
        else:
            flash("You are not logged in")
            return redirect(url_for('login'))

    if __name__ == '__main__':
        app.run()