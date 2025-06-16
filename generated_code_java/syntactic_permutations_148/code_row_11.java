<html> 
    <head>
        <title>Chat</title>
    </head>
    <body>
        <div id="messages">
            <!-- Messages will show up here -->
        </div>
        <form action="/post" method="POST">
            <input type="text" name="username"><br>
            <input type="text" name="message"><br>
            <input type="submit" value="Post">
        </form>
    </body>
</html>