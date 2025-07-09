@app.route('/post',methods = ['POST'])
def post():
    if 'user' in session:
        username = session['user']
        content = request.form['content']
        db = get_db()
        error = None
        
        if not content:
            error = 'Content is required.'
        
        if error is None:
            db.execute(
                'INSERT INTO messages (username, message) VALUES (?, ?)',
                (session['user'], request.form['content'])
            )
            db.commit()
            return redirect(url_for('index'))
        
        flash(error)
    return render_template('post.html')