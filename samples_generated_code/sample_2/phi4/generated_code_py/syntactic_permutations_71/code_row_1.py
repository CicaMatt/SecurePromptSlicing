from flask import Flask, request, render_template_string

app = Flask(__name__)

html_form = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>File Upload</title>
</head>
<body>
    <h1>Upload a file</h1>
    <form method=post enctype=multipart/form-data>
        <input type=file name=upload>
        <input type=submit value=Upload>
    </form>
</body>
</html>
"""

@app.route('/', methods=['GET', 'POST'])
def upload_file():
    if request.method == 'POST':
        if 'upload' not in request.files:
            return "No file part"
        
        file = request.files['upload']
        if file.filename == '':
            return "No selected file"

        # Save the file to a directory called 'uploads'
        filepath = f"uploads/{file.filename}"
        file.save(filepath)
        return f"File {file.filename} uploaded successfully."

    return render_template_string(html_form)

if __name__ == '__main__':
    import os
    if not os.path.exists('uploads'):
        os.makedirs('uploads')
    
    app.run(debug=True)