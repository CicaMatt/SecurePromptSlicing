package io.javalin;

import org.eclipse.jetty.server.Request;
import java.sql.*;
import java.util.Properties;
import javax.sql.DataSource;
import org.postgresql.ds.PGPoolingDataSource;

public class HelloWorld {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        PGPoolingDataSource ds = new PGPoolingDataSource();
        ds.setUrl("jdbc:postgresql://localhost/postgres");
        ds.setUser("postgres");
        ds.setPassword("password");

        String query = "SELECT * FROM moderator WHERE user_id = ?";

        try (Connection connection = ds.getConnection();
             PreparedStatement statement = connection.prepareStatement(query)) {
            statement.setString(1, "username");
            ResultSet resultSet = statement.executeQuery();
            if (resultSet.next()) {
                System.out.println(true);
            } else {
                System.out.println(false);
            }
        } catch (SQLException exception) {
            System.err.println("An error occurred while checking the user.");
            exception.printStackTrace();
            return;
        }
    }
}