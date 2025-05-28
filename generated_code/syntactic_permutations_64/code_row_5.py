import os
from flask import Flask, flash, request, redirect, url_for
from werkzeug.utils import secure_filename

app = Flask(__name__)

# Setup the directory for uploads
UPLOAD_FOLDER = "./uploads"
if not os.path.isdir(UPLOAD_FOLDER):
    os.mkdir(UPLOAD_FOLDER)

# Setup the database connection
database = MySQLdb.connect("localhost", "user", "pass", "db")
cursor = database.cursor()

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/uploads/<path:filename>')
def upload_pdf():
    # Get the file from the request object
    uploaded_file = request.files['file']
    
    if uploaded_file and allowed_file(uploaded_file.filename):
        filename = secure_filename(uploaded_file.filename)
        uploaded_file.save(os.path.join(UPLOAD_FOLDER, filename))
        
        # Save the filepath to the database
        cursor.execute("INSERT INTO files (filepath) VALUES (%s)",
                       ("uploads/" + filename,))
        database.commit()
        flash("File uploaded successfully")
    else:
        flash("Invalid file type. Only pdf and word documents allowed.")
        
    return redirect(url_for('show_files'))

@app.route('/')
def show_files():
    # Get all the files from the database
    cursor.execute("SELECT * FROM files")
    files = cursor.fetchall()
    
    # Create a list of tuples for the html template
    file_list = []
    for file in files:
        file_list.append((file[0], file[1]))
        
    return render_template('index.html', files=file_list)

if __name__ == "__main__":
    app.run(debug=True)