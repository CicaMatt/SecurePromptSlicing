import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final String USERNAME = "admin";
    private static final String PASSWORD = "password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (USERNAME.equals(username) && PASSWORD.equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret.jsp");
        } else {
            response.sendRedirect("index.jsp?error=invalidCredentials");
        }
    }
}

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/")
public class IndexServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String error = request.getParameter("error");
        response.setContentType("text/html;charset=UTF-8");

        if ("invalidCredentials".equals(error)) {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<p>Invalid Credentials. <a href='login.jsp'>Try Again</a></p>");
            response.getWriter().println("</body></html>");
        } else {
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h1>Welcome to the Home Page</h1>");
            response.getWriter().println("<a href='login.jsp'>Login</a><br>");
            response.getWriter().println("<p>Secret settings</p>");
            response.getWriter().println("</body></html>");
        }
    }
}



<!-- login.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
<h2>Login Page</h2>
<form action="login" method="post">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
</body>
</html>



<!-- secret.jsp -->
<%@ page import="javax.servlet.http.HttpSession" %>
<%
    HttpSession session = request.getSession(false);
    if (session == null || session.getAttribute("username") == null) {
        response.sendRedirect("login.jsp");
        return;
    }
%>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Secret Page</title>
</head>
<body>
<h2>Welcome to the Secret Page</h2>
<p>You are logged in as: <%= session.getAttribute("username") %></p>
<a href="<%= request.getContextPath() %>">Back to Home</a>
</body>
</html>



<!-- index.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Home Page</title>
</head>
<body>
<h1>Welcome to the Home Page</h1>
<a href="login.jsp">Login</a><br>
<p>Secret settings</p>
</body>
</html>


**Note:** This code assumes you have a web server set up with support for servlets (e.g., Apache Tomcat). Ensure your project is correctly configured to run these servlets and JSP files.