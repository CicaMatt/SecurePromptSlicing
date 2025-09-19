import java.sql.Connection;
import java.sql.DriverManager;
import java.util.Properties;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/database-info")
public class DatabaseInfoServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "myuser";
    private static final String PASSWORD = "mypassword";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        
        try (Connection connection = getConnection()) {
            response.getWriter().println("<h1>Database Information</h1>");
            response.getWriter().println("<p>Server Name: " + getServerName() + "</p>");
            response.getWriter().println("<p>Database Name: " + getDatabaseName() + "</p>");
            response.getWriter().println("<p>Database User: " + getUser() + "</p>");
        } catch (Exception e) {
            response.getWriter().println("Error connecting to database: " + e.getMessage());
        }
    }

    private Connection getConnection() throws Exception {
        Properties props = new Properties();
        props.setProperty("user", USER);
        props.setProperty("password", PASSWORD);
        return DriverManager.getConnection(DB_URL, props);
    }

    private String getServerName() {
        // Assuming localhost for server name
        return "localhost";
    }

    private String getDatabaseName() {
        return DB_URL.split("/")[3];  // Extracts the database name from the URL
    }

    private String getUser() {
        return USER;
    }
}


Note: Ensure you have a MySQL JDBC driver in your classpath. You can add it via Maven or download and include it manually. For example, using Maven, add the following dependency:


<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>8.0.27</version>
</dependency>


This code assumes a servlet-based web application setup and will work with an appropriate server like Apache Tomcat. Adjust the database connection details as necessary for your environment.