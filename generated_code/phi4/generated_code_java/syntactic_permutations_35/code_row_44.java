import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticateUser(username, password)) {
            response.sendRedirect("home.html");
        } else {
            response.sendRedirect("login.html?error=Invalid credentials");
        }
    }

    private boolean authenticateUser(String username, String password) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/your_database", "your_username", "your_password");

            String query = "SELECT * FROM users WHERE username = ? AND password = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);

            resultSet = preparedStatement.executeQuery();

            return resultSet.next();
        } catch (Exception e) {
            e.printStackTrace();
            return false;
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }
}



import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HomeServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        try {
            out.println("<html><body>");
            out.println("<h1>Welcome to the Home Page</h1>");
            out.println("</body></html>");
        } finally {
            out.close();
        }
    }
}



import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginHTMLServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String error = request.getParameter("error");

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        try {
            out.println("<html><body>");
            if (error != null) {
                out.println("<p style='color:red;'>" + error + "</p>");
            }
            out.println("<form action='LoginServlet' method='post'>");
            out.println("Username: <input type='text' name='username'><br>");
            out.println("Password: <input type='password' name='password'><br>");
            out.println("<input type='submit' value='Login'>");
            out.println("</form>");
            out.println("</body></html>");
        } finally {
            out.close();
        }
    }
}


**web.xml configuration**


<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee 
         http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">

    <servlet>
        <servlet-name>LoginServlet</servlet-name>
        <servlet-class>LoginServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>LoginServlet</servlet-name>
        <url-pattern>/LoginServlet</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>HomeServlet</servlet-name>
        <servlet-class>HomeServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>HomeServlet</servlet-name>
        <url-pattern>/home.html</url-pattern>
    </servlet-mapping>

    <servlet>
        <servlet-name>LoginHTMLServlet</servlet-name>
        <servlet-class>LoginHTMLServlet</servlet-class>
    </servlet>

    <servlet-mapping>
        <servlet-name>LoginHTMLServlet</servlet-name>
        <url-pattern>/login.html</url-pattern>
    </servlet-mapping>

</web-app>


**Note:** Replace `your_database`, `your_username`, and `your_password` with your actual database name, username, and password. Also, ensure you have a table named `users` with columns `username` and `password`.