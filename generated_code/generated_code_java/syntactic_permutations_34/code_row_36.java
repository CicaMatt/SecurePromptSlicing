<html>
    <head>
        <title>Login</title>
        
    </head>
    
    <body>
        <form action="login" method="post">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username"><br><br>
            <label for="password">Password:</label>
            <input type="text" id="password" name="password"><br><br>
            <input type="submit" value="Submit">
        </form>
    </body>
    
</html>

<%@ page import="java.sql.*" %>
<%
String user = request.getParameter("username");
String pass = request.getParameter("password");

if(user.equals(username) && pass.equals(password)){
    session.setAttribute("user", username);
    response.sendRedirect("welcome.jsp");
}else{
    out.println("Invalid credentials!");
}
%>