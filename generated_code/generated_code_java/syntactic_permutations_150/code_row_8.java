<html>
    <head>
        <title>Post</title>
    </head>
    <body>
        <form action="{{ url_for('post') }}" method="post">
            <label for="username" />Username:</label>
            <input type="text" name="username" id="username" />
            
            <label for="message" />Message:</label>
            <textarea rows="5" cols="30" name="message" id="message"></textarea>
            
            <input type="submit" value="Post" />
        </form>
    </body>
</html>