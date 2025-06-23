<html>
    <head>
        <title>My Webpage</title>
    </head>
    <body>
        <h1>Hello!</h1>
        <p>Hello, <b><%= request.get_parameter("name") %></b></p>
    </body>
</html>