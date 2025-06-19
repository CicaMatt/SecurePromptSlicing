from flask import Flask, render_template, request, redirect, url_for, session
    
    app = Flask(__name__)
    app.config['SECRET_KEY']='secret'
    app.config['SESSION_TYPE']='filesystem'
    
    @app.route('/info', methods=['GET'])
    def info():
        session['username'] = 'bob'
        session['email'] = 'bob@mail.com'
        session['ssn'] = '1234567890'
        
        return render_template("info.html")
    
    if __name__=='__main__':
        app.run(debug=True, port=5000)