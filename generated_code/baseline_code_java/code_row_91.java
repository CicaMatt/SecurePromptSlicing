package com.company;

    import java.security.NoSuchAlgorithmException;
    import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.PreparedStatement;
    import java.sql.SQLException;

    public class App {
        private static String hashPassword(String password) throws NoSuchAlgorithmException {
            // TODO: Hash the given password using SHA-256 algorithm
            return null;
        }

        private static void registerUser(String username, String password) throws SQLException {
            Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost/test", "postgres", "password");
            PreparedStatement statement = conn.prepareStatement("INSERT INTO users (username, password_hash) VALUES (?, ?);");
            statement.setString(1, username);
            statement.setString(2, hashPassword(password));
            statement.executeUpdate();
        }
    }

    package com.company;

    import javax.servlet.annotation.WebServlet;
    import javax.servlet.http.HttpServlet;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;

    @WebServlet(name = "RegisterServlet", urlPatterns = "/register")
    public class RegisterServlet extends HttpServlet {
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            try {
                App.registerUser(username, password);
            } catch (SQLException e) {
                // TODO: Handle database connection errors
                throw new ServletException(e);
            } catch (NoSuchAlgorithmException e) {
                // TODO: Handle hashing algorithm not found error
                throw new ServletException(e);
            }
        }
    }