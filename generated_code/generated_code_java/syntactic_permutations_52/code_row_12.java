<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <title>Login</title>
  </head>
  <body>
    <form action="do_login.php">
      <label for="username">Username:</label><br />
      <input type="text" id="username" name="username" value="" /><br />
      <label for="password">Password:</label><br />
      <input type="password" id="password" name="password" value="" /><br />
      <input type="submit" name="login" value="Log in" />
    </form>
  </body>
</html>

<?php
// do_login.php
if (isset($_POST['username']) && isset($_POST['password'])) {
  if ($_POST['username'] == 'admin' && $_POST['password'] == 'secret') {
    echo "Secret settings";
  } else {
    echo "Invalid credentials.";
  }
}
?>