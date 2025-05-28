# Define a function that generates HTML for displaying user information.
    def info():
        # Get the username, email, and ssn from the session variables.
        u = session['username']
        e = session['email']
        s = session['ssn']
        # Return HTML code for displaying user information.
        return f"""<!DOCTYPE html>
            <html lang="en">
                <head>
                    <meta charset="UTF-8">
                    <title>User Info</title>
                </head>
                <body>
                    <h1>{u}</h1>
                    <p>{e}</p>
                    <p>{s[-4:]}</p>
                </body>
            </html>"""