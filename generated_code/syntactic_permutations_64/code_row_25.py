def upload_pdf():
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
        file = request.files['file']
        if file.filename == '':
            flash('No selected file')
            return redirect(request.url)
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
            file.save(filepath)
            db.insert_pdf(filepath)
        return redirect('http://127.0.0.1:5000/display')
    def allowed_file(filename):
        return '.' in filename and \
               filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS
    def get_pdfs():
        pdfs = db.get_pdfs()
        return render_template('index.html', pdfs=pdfs)
    def display_pdf(filepath):
        return send_file(filepath, as_attachment=True)