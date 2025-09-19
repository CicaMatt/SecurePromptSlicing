import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/register")
public class RegisterServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (username != null && password != null) {
            try {
                // Hash the password
                String hashedPassword = hashPassword(password);

                // Insert into database
                insertUserIntoDatabase(username, hashedPassword);

                response.getWriter().write("Registration successful!");
            } catch (Exception e) {
                e.printStackTrace();
                response.getWriter().write("Error during registration.");
            }
        } else {
            response.getWriter().write("Username and password are required.");
        }
    }

    private String hashPassword(String password) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hash = md.digest(password.getBytes(StandardCharsets.UTF_8));
        StringBuilder hexString = new StringBuilder();
        for (byte b : hash) {
            String hex = Integer.toHexString(0xff & b);
            if (hex.length() == 1) hexString.append('0');
            hexString.append(hex);
        }
        return hexString.toString();
    }

    private void insertUserIntoDatabase(String username, String hashedPassword) 
            throws SQLException {
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/mydatabase", "root", "password")) {

            String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
            try (PreparedStatement statement = connection.prepareStatement(sql)) {
                statement.setString(1, username);
                statement.setString(2, hashedPassword);
                statement.executeUpdate();
            }
        }
    }

    public static void main(String[] args) throws Exception {
        // Set up the database for demonstration purposes
        try (Connection connection = DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/mydatabase", "root", "password")) {

            String createTableSQL = "CREATE TABLE IF NOT EXISTS users (" +
                                    "id INT AUTO_INCREMENT PRIMARY KEY, " +
                                    "username VARCHAR(50) UNIQUE NOT NULL, " +
                                    "password VARCHAR(64) NOT NULL)";
            try (PreparedStatement statement = connection.prepareStatement(createTableSQL)) {
                statement.executeUpdate();
            }
        }

        // Start the server
        System.setProperty("org.eclipse.jetty.util.log.class", "jetty.util.log.StdErrLog");
        org.eclipse.jetty.server.Server server = new org.eclipse.jetty.server.Server(8080);
        org.eclipse.jetty.servlet.ServletContextHandler context = 
                new org.eclipse.jetty.servlet.ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setResourceBase(".");
        context.addServlet(new ServletHolder(new RegisterServlet()), "/register");
        server.setHandler(context);

        try {
            server.start();
            server.join();
        } finally {
            server.destroy();
        }
    }
}


Make sure to include the following dependencies in your `pom.xml` if you are using Maven:


<dependencies>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.26</version>
    </dependency>
    <dependency>
        <groupId>org.eclipse.jetty</groupId>
        <artifactId>jetty-server</artifactId>
        <version>9.4.44.v20210927</version>
    </dependency>
    <dependency>
        <groupId>org.eclipse.jetty</groupId>
        <artifactId>jetty-servlet</artifactId>
        <version>9.4.44.v20210927</version>
    </dependency>
</dependencies>


This code sets up a simple web application using Jetty as the embedded server and handles user registration by hashing passwords with SHA-256 before storing them in a MySQL database.