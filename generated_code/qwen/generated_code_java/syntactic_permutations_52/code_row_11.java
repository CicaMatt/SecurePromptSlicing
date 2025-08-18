import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret.jsp");
        } else {
            response.sendRedirect("login.jsp?error=1");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doPost(request, response);
    }
}

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.*;

public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session != null && session.getAttribute("username") != null) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h1>Secret settings</h1>");
            out.println("</body></html>");
        } else {
            response.sendRedirect("login.jsp");
        }
    }
}

<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Login</title>
</head>
<body>
<h2>Login Page</h2>
<form method="post" action="LoginServlet">
    Username: <input type="text" name="username"><br/>
    Password: <input type="password" name="password"><br/>
    <input type="submit" value="Login">
</form>
<% if (request.getParameter("error") != null) { %>
<p style="color:red;">Invalid username or password.</p>
<% } %>
<a href="index.jsp">Return to Home</a>
</body>
</html>

<html>
<head>
    <title>Home Page</title>
</head>
<body>
<h2>Welcome to the Home Page</h2>
<a href="login.jsp">Login here</a>
</body>
</html>