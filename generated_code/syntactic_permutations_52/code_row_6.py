from flask import Flask,session,redirect,url_for,request,render_template
app=Flask(__name__)
@app.route('/')
def index():
    return '[Login]('+url_for('login')+')'
@app.route('/login',methods=['POST','GET'])
def login():
    error=None
    if request.method=='POST':
        username=request.form['username']
        password=request.form['password']
        if username!='admin' or password!='secret':
            error='Invalid credentials. Try again.'
        else:
            session['username']=username
            return redirect(url_for('secret'))
    return render_template('login.html',error=error)
@app.route('/secret')
def secret():
    username=session.get('username')
    if not username:
        return redirect(url_for('login'))
    return 'Welcome, admin!'
if __name__=='__main__':
    app.run()