def login():
        return render_template('login.html')

    @app.route('/do-login', methods=['POST'])
    def do_login():
        if request.method == 'POST':
            username = request.form['username']
            password = request.form['password']
            cur = mysql.connection.cursor()
            result = cur.execute("SELECT * FROM users WHERE username=%s AND password=%s", [username, password])
            if result > 0:
                session['loggedin'] = True
                session['id'] = request.form['username']
                flash('You are now logged in', 'success')
                return redirect(url_for('dashboard'))
            else:
                flash('Invalid username or password', 'danger')
                return render_template('login.html', error=error)
        return render_template('login.html')
    @app.route('/')
    def index():
        cur = mysql.connection.cursor()
        resultValue = cur.execute("SELECT * FROM posts")
        posts = cur.fetchall()
        if resultValue > 0:
            return render_template('index.html', posts=posts)
        else:
            msg = 'No Posts Found'
            return render_template('index.html', msg=msg)
    @app.route('/user/<string:id>')
    def user_page(id):
        cur = mysql.connection.cursor()
        resultValue = cur.execute("SELECT * FROM posts WHERE author=%s", [id])
        posts = cur.fetchall()
        if resultValue > 0:
            return render_template('user_page.html', posts=posts, id=id)
        else:
            msg = 'No Posts Found'
            return render_template('user_page.html', msg=msg, id=id)
    @app.route('/admin')
    def admin_page():
        cur = mysql.connection.cursor()
        resultValue = cur.execute("SELECT * FROM users")
        users = cur.fetchall()
        if resultValue > 0:
            return render_template('admin_page.html', users=users)
        else:
            msg = 'No Users Found'
            return render_template('admin_page.html', msg=msg)

### Test case 1:
    >>>>>>>>
    Enter the value for x: 4
    The factorial of 4 is 24
    >>>>>>>>
    Enter the value for x: 6
    The factorial of 6 is 720
    
### Test case 2:
    >>>>>>>>
    Enter the value for x: -3
    Invalid input. Factorial is not defined for negative numbers.