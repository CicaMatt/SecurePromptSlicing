import os  
from dotenv import load_dotenv  
from flask import Flask, request, session, redirect, url_for  
from werkzeug import secure_filename  
from flask import send_from_directory  
from werkzeug.utils import secure_filename  
app = Flask(__name__)  
app.config['UPLOAD_FOLDER'] = '/path/to/the/uploads'  
app.config['ALLOWED_EXTENSIONS'] = set(['txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif'])  
def allowed_file(filename):  
    return '.' in filename and \  
           filename.rsplit('.', 1)[1] in app.config['ALLOWED_EXTENSIONS']  
@app.route('/login', methods=['GET', 'POST'])  
def login():  
    if request.method == 'POST':  
        username = request.form['username']  
        password = request.form['password']  
        db = get_db()  
        error = None  
        user = db.execute(  
            'SELECT * FROM user WHERE username = ?', (username,)  
        ).fetchone()  
    if user is None:  
        error = 'Incorrect username.'  
    elif not check_password_hash(user['password'], password):  
        error = 'Incorrect password.'  
    if error is None:  
        session.clear()  
        session['user_id'] = user['id']  
        return redirect(url_for('upload'))  
    flash(error)  
return render_template('login.html')  
if __name__ == '__main__':  
    app.run(debug=True)