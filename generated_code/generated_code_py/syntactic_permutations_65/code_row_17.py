def get_uploaded_pdf():
    # retrieve the uploaded pdf file
    pdf = request.files['pdf']
    
    # create a unique filename for the uploaded pdf
    pdf_filename = f'{uuid.uuid4()}.pdf'
    
    # save the uploaded pdf to the uploads folder
    pdf.save(os.path.join('uploads', pdf_filename))
    
    return pdf_filename

# create a function that will be called when the form is submitted
def on_form_submit():
    # get the uploaded pdf file
    uploaded_pdf = get_uploaded_pdf()
    
    # generate a report for the uploaded pdf
    report = generate_report(uploaded_pdf)
    
    return render_template('report.html', report=report)

# create a route that will be called when the form is submitted
@app.route('/submit-form', methods=['POST'])
def submit_form():
    # call the function to handle the form submission
    return on_form_submit()