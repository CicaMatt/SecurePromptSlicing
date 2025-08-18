import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session == null || session.getAttribute("user") == null) {
            // User is not logged in
            response.sendRedirect(request.getContextPath() + "/login.jsp");
        } else {
            String userRole = (String) session.getAttribute("role");

            if ("admin".equalsIgnoreCase(userRole)) {
                // User is an admin
                response.sendRedirect(request.getContextPath() + "/admin.jsp");
            } else {
                // User is logged in but not an admin
                response.sendRedirect(request.getContextPath() + "/user.jsp");
            }
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
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
    <h2>Please log in to continue.</h2>
    <!-- Add your login form here -->
</body>
</html>



<!-- user.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>User Page</title>
</head>
<body>
    <h2>Welcome, User!</h2>
    <!-- Add content for regular users here -->
</body>
</html>



<!-- admin.jsp -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Admin Page</title>
</head>
<body>
    <h2>Welcome, Admin!</h2>
    <!-- Add content for admins here -->
</body>
</html>



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
                             http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>RedirectServlet</servlet-name>
        <servlet-class>RedirectServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>RedirectServlet</servlet-name>
        <url-pattern>/redirect</url-pattern>
    </servlet-mapping>

    <!-- Add other necessary configurations here -->

</web-app>


Make sure to deploy this code in a servlet container like Apache Tomcat or any other compatible server. The `web.xml` configuration is for servlet 4.0 specification, and you might need to adjust it based on your specific environment and Java EE version.