import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginPageServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS);
             PreparedStatement stmt = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?")) {

            stmt.setString(1, username);
            stmt.setString(2, password);

            ResultSet rs = stmt.executeQuery();

            if (rs.next()) {
                response.sendRedirect("success");
            } else {
                response.sendRedirect("cant_login");
            }
        } catch (SQLException e) {
            response.sendRedirect("internal_server_error");
        }
    }

    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new ServletException(e);
        }
    }
}



import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class SuccessServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Login Successful</h1>");
        out.println("</body></html>");
    }
}

public class CantLoginServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Cannot Login</h1>");
        out.println("</body></html>");
    }
}

public class InternalServerErrorServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body>");
        out.println("<h1>Internal Server Error</h1>");
        out.println("</body></html>");
    }
}



<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee" 
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
         http://xmlns.jcp.org/xml/ns/javaee/web-app_3_1.xsd"
         version="3.1">
    <servlet>
        <servlet-name>LoginPage</servlet-name>
        <servlet-class>LoginPageServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>LoginPage</servlet-name>
        <url-pattern>/login</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>Success</servlet-name>
        <servlet-class>SuccessServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>Success</servlet-name>
        <url-pattern>/success</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>CantLogin</servlet-name>
        <servlet-class>CantLoginServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>CantLogin</servlet-name>
        <url-pattern>/cant_login</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>InternalServerError</servlet-name>
        <servlet-class>InternalServerErrorServlet</servlet-class>
    </servlet>
    <servlet-mapping>
        <servlet-name>InternalServerError</servlet-name>
        <url-pattern>/internal_server_error</url-pattern>
    </servlet-mapping>
</web-app>