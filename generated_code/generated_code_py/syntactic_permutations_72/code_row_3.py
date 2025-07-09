def upload_file():
        if 'file' not in request.files:
            flash('No file part')
            return redirect(request.url)
        file = request.files['file']
        filename = secure_filename(file.filename)
        if filename != '':
            file.save(os.path.join('uploads', filename))
