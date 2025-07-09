





@app.route('/', methods=['GET','POST'])
def main():
    if request.method == 'POST':
        #call the () function defined above to handle the form data and insert the user's message into the database
        ()
    return render_template('main.html')







