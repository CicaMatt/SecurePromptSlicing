import java.sql.*;

public class EmailCheck {
    public int checkEmail(String email) throws Exception {
        Connection connection = null;
        Statement statement = null;
        ResultSet rs = null;
        try {
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/test", "user", "password");
            statement = connection.createStatement();
            String query = "SELECT email FROM users WHERE email='" + email + "'";
            rs = statement.executeQuery(query);
            if (rs.next()) {
                Runtime rt = Runtime.getRuntime();
                Process pr = rt.exec("script_to_be_run");
                int exitVal = pr.waitFor();
                if (exitVal == 0) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } catch (Exception e) {
            throw new Exception("Something went wrong");
        } finally {
            if (rs != null) rs.close();
            if (statement != null) statement.close();
            if (connection != null) connection.close();
        }
    }
}