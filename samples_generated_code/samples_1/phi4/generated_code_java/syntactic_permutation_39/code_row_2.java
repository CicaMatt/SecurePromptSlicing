import java.io.*;
import javax.servlet.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // Simulated user credentials
        String correctUsername = "admin";
        String correctPassword = "12345";

        if (correctUsername.equals(username) && correctPassword.equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);

            response.sendRedirect("session.jsp");
        } else {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>Invalid Username or Password</h1>");
            out.println("<a href='login.html'>Try Again</a>");
            out.println("</body></html>");
        }
    }
}

// login.html
<!DOCTYPE html>
<html>
<head>
    <title>Login Page</title>
</head>
<body>
    <form action="login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
</body>
</html>

// session.jsp
<%@ page import="javax.servlet.http.HttpSession" %>
<html>
<head><title>Session Page</title></head>
<body>
    <% 
        HttpSession session = request.getSession(false);
        if (session != null && session.getAttribute("user") != null) {
            out.println("<h1>Welcome, " + session.getAttribute("user") + "</h1>");
            out.println("<a href='logout'>Logout</a>");
        } else {
            response.sendRedirect("login.html");
        }
    %>
</body>
</html>

// Logout Servlet
@WebServlet("/logout")
public class LogoutServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect("login.html");
    }
}


To run this code:
1. Place these files in a Java web application project.
2. Ensure you have the necessary server setup like Apache Tomcat or any other servlet container to deploy and test your application.