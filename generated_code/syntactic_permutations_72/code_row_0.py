def upload_file():
    p = request.files['file']
    if p.filename != '':
        p.save(os.path.join('uploads', filename))
        return redirect(url_for("success"))
    else:
        return redirect(url_for("failure"))