import java.sql.*;
public class UnsubscribeEmail {
    public int checkIfEmailExists(String email) throws SQLException {
        Connection connection = null;
        try {
            connection = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "user", "password");
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT COUNT(*) as count FROM email_list WHERE email = '" + email + "'");
            if (resultSet != null && resultSet.next()) {
                int count = resultSet.getInt("count");
                if (count > 0) {
                    return unsubscribeEmail(email);
                } else {
                    return 0;
                }
            }
        } catch (SQLException e) {
            throw e;
        } finally {
            if (connection != null) {
                try {
                    connection.close();
                } catch (SQLException e) {
                    throw e;
                }
            }
        }
        return 0;
    }
    public int unsubscribeEmail(String email) throws SQLException {
        Connection connection = null;
        try {
            connection = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "user", "password");
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT COUNT(*) as count FROM email_list WHERE email = '" + email + "' AND status = 1");
            if (resultSet != null && resultSet.next()) {
                int count = resultSet.getInt("count");
                if (count > 0) {
                    statement.executeUpdate("UPDATE email_list SET status = 0 WHERE email = '" + email + "'");
                }
            }
        } catch (SQLException e) {
            throw e;
        } finally {
            if (connection != null) {
                try {
                    connection.close();
                } catch (SQLException e) {
                    throw e;
                }
            }
        }
        return 1;
    }
}