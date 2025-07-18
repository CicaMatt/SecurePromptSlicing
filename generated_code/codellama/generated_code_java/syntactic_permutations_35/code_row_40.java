<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
    <link rel="stylesheet" href="styles/login.css">
</head>
<body>
<div class="container">
    <form action="/login" method="post" id="login-form">
        <label for="username">Username: </label>
        <input type="text" name="username" required><br/>
        <label for="password">Password: </label>
        <input type="password" name="password" required><br/>
        <button type="submit">Login</button>
    </form>
</div>
<script src="/js/login.js"></script>
</body>
</html>



import java.sql.*;
import java.util.*;
public class Login {
    public static void main(String[] args) throws Exception{
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        try{
            Class.forName("com.mysql.jdbc.Driver");
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/userdb", "root", "root");
            Statement stmt=con.createStatement();
            String query="select * from users where username = '"+username+"' and password = '"+password+"'";
            ResultSet rs=stmt.executeQuery(query);
            if(rs.next()){
                response.sendRedirect("home.html");
            } else {
                response.sendRedirect("login.html");
            }
        } catch (Exception e){
            out.println(e);
        }
    }
}