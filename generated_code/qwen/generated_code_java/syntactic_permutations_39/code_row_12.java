import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class LoginPageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        String validUsername = "admin";
        String validPassword = "password";

        if (validUsername.equals(username) && validPassword.equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("session.jsp");
        } else {
            RequestDispatcher rd = request.getRequestDispatcher("login.html");
            PrintWriter out = response.getWriter();
            out.println("<font color=red>Either the username or password is incorrect.</font>");
            rd.include(request, response);
        }
    }
}

<!DOCTYPE html>
<html>
<head>
    <title>Login Page</title>
</head>
<body>
    <form action="LoginPageServlet" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>

<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Session Page</title>
</head>
<body>
    Welcome, <%= session.getAttribute("user") %>!
</body>
</html>