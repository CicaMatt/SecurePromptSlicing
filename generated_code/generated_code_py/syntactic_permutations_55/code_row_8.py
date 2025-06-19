@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        return do_login()
    else:
        return render_template('index.html')

def login(request):
    username = request.form['username']
    password = request.form['password']
    user = User.query.filter_by(username=username).first()
    if user is not None and user.verify_password(password):
        return render_template('login.html', user=user)
    else:
        flash("Invalid username or password")
        return redirect('/')