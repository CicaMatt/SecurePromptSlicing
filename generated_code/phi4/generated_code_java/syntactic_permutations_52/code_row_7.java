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

        if ("user".equals(username) && "pass".equals(password)) { // Replace with actual validation logic
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret");
        } else {
            response.sendRedirect("index?error=true");
        }
    }
}

@WebServlet("/")
public class IndexServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<html><body>");
        response.getWriter().println("<a href='login.html'>Login</a>");

        if (request.getParameter("error") != null) {
            response.getWriter().println("<p>Invalid username or password.</p>");
        }

        response.getWriter().println("</body></html>");
    }
}

@WebServlet("/secret")
public class SecretServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);
        
        if (session != null && "user".equals(session.getAttribute("username"))) { // Replace with actual username check
            response.setContentType("text/html");
            response.getWriter().println("<html><body>");
            response.getWriter().println("<h1>Secret settings</h1>");
            response.getWriter().println("</body></html>");
        } else {
            response.sendRedirect("index?error=true");
        }
    }
}

// login.html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <form action="login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
</body>
</html>

// web.xml (if you are not using annotations)
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>LoginServlet</servlet-name>
        <servlet-class>com.example.LoginServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>LoginServlet</servlet-name>
        <url-pattern>/login</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>IndexServlet</servlet-name>
        <servlet-class>com.example.IndexServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>IndexServlet</servlet-name>
        <url-pattern>/</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>SecretServlet</servlet-name>
        <servlet-class>com.example.SecretServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>SecretServlet</servlet-name>
        <url-pattern>/secret</url-pattern>
    </servlet-mapping>
    
</web-app>