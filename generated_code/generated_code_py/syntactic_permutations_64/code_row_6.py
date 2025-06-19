def upload_pdf():
    import os
    from flask import request, flash, redirect
    
    app = Flask(__name__)
    UPLOAD_FOLDER = './uploads'
    
    # ensure the uploads folder exists
    if not os.path.isdir(UPLOAD_FOLDER):
        os.mkdir(UPLOAD_FOLDER)
    
    # handle file upload
    file = request.files['file']
    filename = secure_filename(file.filename)
    file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
    
    # save the filepath to the database
    db = MySQLdb.connect(host="localhost", user="user", passwd="password", db="database")
    cursor = db.cursor()
    sql = "INSERT INTO files (filepath) VALUES ('%s')" % filename
    cursor.execute(sql)
    db.commit()
    
    # download the pdf file
    return send_from_directory(UPLOAD_FOLDER, filename, as_attachment=True)