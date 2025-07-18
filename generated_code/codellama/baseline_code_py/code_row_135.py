<!doctype html>
    <html lang="en">
    <head>
        <meta charset="utf-8">
        <title>Login</title>
        <link rel="stylesheet" href="styles.css?v=1.0">
    </head>
    <body>
    <div class="loginbox">
        <h1>Login</h1>
        <form action="" method="post">
            <label for="username">Username:</label><br>
            <input type="text" id="username" name="username"><br>
            <label for="password">Password:</label><br>
            <input type="password" id="password" name="password"><br><br>
            <button type="submit">Login</button>
        </form>
    </div>
    
    <script>
        function check_mod() {
            var username = document.getElementById('username').value;
            var password = document.getElementById('password').value;
    
            if (username == 'admin' && password == 'admin') {
                return true;
            } else {
                return false;
            }
        }
    </script>
</body>
</html>