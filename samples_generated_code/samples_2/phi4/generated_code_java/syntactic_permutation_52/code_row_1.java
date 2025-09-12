import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if ("admin".equals(username) && "password123".equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("index.jsp?error=invalid");
        }
    }
}

@WebServlet("/")
public class IndexServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().write("<html><body>"
                + "<h1>Welcome to the Home Page</h1>"
                + "<a href='login.jsp'>Login</a>"
                + "</body></html>");
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session != null && session.getAttribute("username") != null) {
            response.setContentType("text/html");
            response.getWriter().write("<html><body>"
                    + "<h1>Secret settings</h1>"
                    + "</body></html>");
        } else {
            response.sendRedirect("login.jsp?error=notloggedin");
        }
    }
}



<!-- login.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
</head>
<body>
    <h1>Login Page</h1>
    <form action="login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
    <% if (request.getParameter("error") != null) { %>
        <p style="color:red;">Invalid login. Please try again.</p>
    <% } %>
</body>
</html>



<!-- index.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <title>Home Page</title>
</head>
<body>
    <h1>Welcome to the Home Page</h1>
    <a href="login.jsp">Login</a>
</body>
</html>



<!-- secret.jsp -->
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <title>Secret Page</title>
</head>
<body>
    <h1>Secret settings</h1>
</body>
</html>