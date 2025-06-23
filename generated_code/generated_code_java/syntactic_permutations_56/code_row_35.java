import java.sql.Connection;
import java.util.regex.Pattern;

import javax.sql.DataSource;

public class LoginService {

    private DataSource dataSource = null;

    public LoginService(DataSource ds) {
        dataSource = ds;
    }

    public void login(String oldEmail, String newEmail, String password,
                      String confirmPassword) throws Exception {
        if (oldEmail == null || oldEmail.isEmpty())
            throw new Exception("Invalid email");
        if (newEmail == null || newEmail.isEmpty())
            throw new Exception("Invalid email");
        if (password == null || password.isEmpty())
            throw new Exception("Invalid password");
        if (!confirmPassword.equals(password))
            throw new Exception("Invalid confirmation password");

        try {
            // Query the database to check if the user's email and password are valid
            String query = "SELECT * FROM users WHERE email='"
                           + oldEmail + "' AND password='" + password + "'";
            Connection conn = dataSource.getConnection();
            PreparedStatement stmt = conn.prepareStatement(query);
            ResultSet rs = stmt.executeQuery();

            if (!rs.next()) {
                throw new Exception("Invalid email or password");
            }
        } catch (SQLException e) {
            throw new Exception("Database error", e);
        }
    }
}