import java.security.*;
import javax.crypto.*;
import javax.crypto.spec.*;
import java.util.*;
import spark.ModelAndView;
import spark.template.velocity.VelocityTemplateEngine;
import static spark.Spark.*;
import org.apache.commons.lang3.StringUtils;
import com.google.common.hash.*;
import com.google.common.io.*;

public class Register {
    public static void main(String[] args) {
        // Database connection information
        String jdbcDriver = "com.mysql.jdbc.Driver";
        String dbUrl = "jdbc:mysql://localhost/mydatabase";
        String user = "username";
        String pass = "password";
        
        // Connect to database and set up hash function
        Connection conn;
        HashFunction hf = Hashing.sha256();
        try {
            Class.forName(jdbcDriver).newInstance();
            conn = DriverManager.getConnection(dbUrl, user, pass);
        } catch (Exception e) {
            System.out.println("Error connecting to database");
            return;
        }
        
        // Set up web application
        port(8080);
        staticFileLocation("/public");
        
        // Define main page
        get("/", (req, res) -> {
            Map<String, Object> model = new HashMap<>();
            return new ModelAndView(model, "index.vtl");
        }, new VelocityTemplateEngine());
        
        // Define registration form submission
        post("/register", (req, res) -> {
            String username = req.queryParams("username");
            String password = req.queryParams("password");
            
            // Check if username is already taken
            boolean usernameTaken = false;
            try {
                PreparedStatement ps = conn.prepareStatement("SELECT * FROM users WHERE username=?");
                ps.setString(1, username);
                ResultSet rs = ps.executeQuery();
                while (rs.next()) {
                    String dbUsername = rs.getString("username");
                    if (dbUsername.equals(username)) {
                        usernameTaken = true;
                        break;
                    }
                }
            } catch (Exception e) {
                System.out.println("Error checking for duplicate username");
                return "Error";
            }
            
            // Hash password and insert into database if username is not taken
            String hashedPassword = hf.hashString(password, StandardCharsets.UTF_8).toString();
            try {
                PreparedStatement ps = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
                ps.setString(1, username);
                ps.setString(2, hashedPassword);
                ps.executeUpdate();
            } catch (Exception e) {
                System.out.println("Error inserting into database");
                return "Error";
            }
            
            // Redirect to main page if successful registration
            res.redirect("/");
            return null;
        });
    }
}