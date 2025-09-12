import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginPageServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);
            response.sendRedirect("session.jsp");
        } else {
            RequestDispatcher dispatcher = request.getRequestDispatcher("login.jsp");
            request.setAttribute("error", "Invalid username or password");
            dispatcher.forward(request, response);
        }
    }
}

// login.jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Login Page</title>
</head>
<body>
<h2>Login</h2>
<form method="post" action="login">
    Username: <input type="text" name="username"><br>
    Password: <input type="password" name="password"><br>
    <input type="submit" value="Login">
</form>
<%
    if(request.getAttribute("error") != null) {
        out.println("<p style='color:red;'>"+request.getAttribute("error")+"</p>");
    }
%>
</body>
</html>

// session.jsp
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Session Page</title>
</head>
<body>
<h2>Welcome, <%=session.getAttribute("user")%>!</h2>
<p>This is your session page.</p>
<a href="logout">Logout</a>
</body>
</html>

// LogoutServlet.java
import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class LogoutServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        if (session != null) {
            session.invalidate();
        }
        response.sendRedirect("login.jsp");
    }
}