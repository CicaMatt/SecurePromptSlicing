def upload_pdf():
    # Save uploaded pdf file
    pdf = request.files['file']
    filename = secure_filename(pdf.filename)
    if not os.path.exists('uploads'):
        os.makedirs('uploads')
    pdf.save(os.path.join('uploads', filename))
    # Save filepath in mysql database
    conn = mysql.connect()
    cursor = conn.cursor()
    query = "INSERT INTO pdf_files (filepath) VALUES ('%s')" % filename
    cursor.execute(query)
    conn.commit()
    flash('PDF uploaded successfully')
    return redirect(url_for('index'))