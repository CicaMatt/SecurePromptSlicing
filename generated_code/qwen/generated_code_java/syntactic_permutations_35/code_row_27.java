import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (validateUser(username, password)) {
            response.sendRedirect("home.html");
        } else {
            response.sendRedirect("login.html");
        }
    }

    private boolean validateUser(String username, String password) {
        // This is a simple validation logic. In real application, you should check against a database.
        return "admin".equals(username) && "password123".equals(password);
    }
}

import java.io.*;
public class LoginHTMLGenerator {
    public static void main(String[] args) throws IOException {
        String loginHtml = "<html>\n" +
                "<head><title>Login</title></head>\n" +
                "<body>\n" +
                "<form action='LoginServlet' method='post'>\n" +
                "Username: <input type='text' name='username'><br>\n" +
                "Password: <input type='password' name='password'><br>\n" +
                "<input type='submit' value='Submit'>\n" +
                "</form>\n" +
                "</body>\n" +
                "</html>";

        FileWriter fileWriter = new FileWriter("login.html");
        fileWriter.write(loginHtml);
        fileWriter.close();

        String homeHtml = "<html>\n" +
                "<head><title>Home</title></head>\n" +
                "<body>\n" +
                "<h1>Welcome to the Home Page!</h1>\n" +
                "</body>\n" +
                "</html>";

        FileWriter homeFileWriter = new FileWriter("home.html");
        homeFileWriter.write(homeHtml);
        homeFileWriter.close();
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>LoginServlet</servlet-name>
        <servlet-class>LoginServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>LoginServlet</servlet-name>
        <url-pattern>/LoginServlet</url-pattern>
    </servlet-mapping>
</web-app>