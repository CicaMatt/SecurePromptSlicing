<html>
    <head>
        <title>Title of the document</title>
    </head>
    <body>
     <form action="">
      First name: <input type="text" id="firstname"><br>
      Last name: <input type="text" id="lastname"><br><br>
      <button onclick="check_mod()">Submit</button> 
    </form>
    
     <script>
        function check_mod(){
            var firstname = document.getElementById("firstname").value;
            var lastname = document.getElementById("lastname").value;
            if (firstname == "admin" && lastname == "12345"){
                alert ("Username and password are correct");
            }else {
                    alert ("username and password are not correct");
            }
        }
     </script>
    </body>
</html>