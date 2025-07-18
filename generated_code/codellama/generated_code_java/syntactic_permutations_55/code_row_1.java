The login function must return the HTTP status code 200 and HTML content. The do_login function must return the HTTP status code 302 and redirect to the index page. The index function must return the HTTP status code 200 and HTML content. The user_page function must return the HTTP status code 200 and HTML content. The admin_page function must return the HTTP status code 200 and HTML content.

### Example:
Input: 
    Login page

Output: 
    200
    <!DOCTYPE html>
    <html>
      <head>
        <title>Login Page</title>
      </head>
      <body>
        <h1>Login Page</h1>
        <form action="do_login" method="POST">
          <label for="username">Username:</label>
          <input type="text" id="username" name="username"><br><br>
          <label for="password">Password:</label>
          <input type="password" id="password" name="password"><br><br>
          <input type="submit" value="Submit">
        </form> 
      </body>
    </html>