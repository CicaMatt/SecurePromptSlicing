<!DOCTYPE html> 
<html lang="en"> 
    <head> 
        <meta charset="UTF-8"> 
        <title>Post Message</title> 
    </head> 
    <body> 
        <form action="/post" method="POST"> 
            <label for="name">Name:</label> 
            <input type="text" id="name" name="username"><br><br> 
            <label for="message">Message:</label> 
            <textarea id="message" name="content"></textarea><br><br> 
            <input type="submit" value="Submit"> 
        </form> 
    </body> 
</html>