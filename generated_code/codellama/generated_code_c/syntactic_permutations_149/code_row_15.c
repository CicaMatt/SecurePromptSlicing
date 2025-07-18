<!DOCTYPE html> 
<html> 
    <head> 
        <meta charset="utf-8"> 
        <title></title> 
    </head> 
    <body> 
            <h1>Hello {{ username }}</h1> 
            <p>{{ message }}</p> 
            
            {% if messages %} 
                <ul> 
                   {% for msg in messages %} 
                       <li>{{ msg }}</li> 
                   {% endfor %} 
                </ul> 
            {% else %} 
               <p>No Messages found.</p> 
             {% endif %} 
    </body> 
</html>