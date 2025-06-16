<!DOCTYPE html> 
     <html lang="en">
      <head>
        <meta charset="UTF-8" />
          <title>Login</title>
       </head>
   <body>
   <form action="/login" method="post">
    Username:<br/>
    <input type="text" name="username"/><br/>
    Password:<br/>
    <input type="password" name="password"/><br/>
    <input type="submit" value="Submit"/>
   </form> 
  </body>
</html>


function login() {
        var username = req.body.username;
        var password = req.body.password;

        if (username == 'admin' && password == 'pass') {
            res.redirect('/home');
        } else {
            res.redirect('/login');
        }
    }