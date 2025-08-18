import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class MainServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        switch (path) {
            case "/login":
                login(request, response);
                break;
            case "/index":
                index(request, response);
                break;
            case "/user_page":
                userPage(request, response);
                break;
            case "/admin_page":
                adminPage(request, response);
                break;
            default:
                response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String path = request.getServletPath();
        if (path.equals("/do_login")) {
            doLogin(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_METHOD_NOT_ALLOWED);
        }
    }

    private void login(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Login</h2>");
        out.println("<form action='do_login' method='post'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("</body></html>");
    }

    private void doLogin(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if ("admin".equals(username) && "admin123".equals(password)) {
            response.sendRedirect("admin_page");
        } else if (username != null && !username.isEmpty()) {
            response.sendRedirect("user_page?user=" + username);
        } else {
            response.sendError(HttpServletResponse.SC_UNAUTHORIZED, "Invalid credentials");
        }
    }

    private void index(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Welcome to the Index Page</h2>");
        out.println("<a href='login'>Login</a>");
        out.println("</body></html>");
    }

    private void userPage(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String user = request.getParameter("user");
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Welcome " + user + "</h2>");
        out.println("<a href='index'>Back to Index</a>");
        out.println("</body></html>");
    }

    private void adminPage(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h2>Welcome Admin</h2>");
        out.println("<a href='index'>Back to Index</a>");
        out.println("</body></html>");
    }
}



<!-- web.xml -->
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">

    <servlet>
        <servlet-name>MainServlet</servlet-name>
        <servlet-class>MainServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>MainServlet</servlet-name>
        <url-pattern>/login</url-pattern>
    </servlet-mapping>
    <servlet-mapping>
        <servlet-name>MainServlet</servlet-name>
        <url-pattern>/do_login</url-pattern>
    </servlet-mapping>
    <servlet-mapping>
        <servlet-name>MainServlet</servlet-name>
        <url-pattern>/index</url-pattern>
    </servlet-mapping>
    <servlet-mapping>
        <servlet-name>MainServlet</servlet-name>
        <url-pattern>/user_page</url-pattern>
    </servlet-mapping>
    <servlet-mapping>
        <servlet-name>MainServlet</servlet-name>
        <url-pattern>/admin_page</url-pattern>
    </servlet-mapping>

</web-app>