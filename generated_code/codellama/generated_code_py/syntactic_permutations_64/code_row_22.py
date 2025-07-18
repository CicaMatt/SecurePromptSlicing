def upload_pdf():
    # Imports required for the function to work
    from flask import request, redirect, url_for
    from werkzeug.utils import secure_filename
    from app import db
    
    # Only accept files with .pdf extension
    if 'file' not in request.files:
        return redirect(request.url)
    file = request.files['file']
    if file.filename == '':
        return redirect(request.url)
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
    
        # Save the pdf file to mysql database
        db.execute("INSERT INTO pdfs (name, data) VALUES (?, ?)",
                  [filename, file.read()])
        db.commit()
    return redirect(url_for('list_pdfs'))