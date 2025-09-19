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
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<html><body>");
            out.println("<h2>Invalid username or password. Please try again.</h2>");
            out.println("<a href='login.html'>Go back to login</a>");
            out.println("</body></html>");
        }
    }
}

// login.html
// <!DOCTYPE html>
// <html>
// <head>
//     <title>Login Page</title>
// </head>
// <body>
//     <h2>Login</h2>
//     <form action="LoginPageServlet" method="post">
//         Username: <input type="text" name="username"><br><br>
//         Password: <input type="password" name="password"><br><br>
//         <input type="submit" value="Login">
//     </form>
// </body>
// </html>

// session.jsp
// <!DOCTYPE html>
// <html>
// <head>
//     <title>Session Page</title>
// </head>
// <body>
//     <h2>Welcome to your session, ${user}!</h2>
//     <a href='logout'>Logout</a>
// </body>
// </html>

// web.xml
// <?xml version="1.0" encoding="UTF-8"?>
// <web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
//          xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
//          xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
//                              http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
//          version="3.1">
//     <servlet>
//         <servlet-name>LoginPageServlet</servlet-name>
//         <servlet-class>LoginPageServlet</servlet-class>
//     </servlet>
//     <servlet-mapping>
//         <servlet-name>LoginPageServlet</servlet-name>
//         <url-pattern>/LoginPageServlet</url-pattern>
//     </servlet-mapping>
//     <welcome-file-list>
//         <welcome-file>login.html</welcome-file>
//     </welcome-file-list>
// </web-app>