import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {
    public static void main(String[] args) {
        Spark.get("/checkModerator/:userId", (Request request, Response response) -> {
            String userId = request.params(":userId");
            return checkIfUserIsModerator(userId);
        });
    }

    private static String checkIfUserIsModerator(String userId) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourDatabase", "username", "password");

            String query = "SELECT is_moderator FROM users WHERE id = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, userId);

            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                boolean isModerator = resultSet.getBoolean("is_moderator");
                return Boolean.toString(isModerator);
            } else {
                return "User not found";
            }
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            return "Database error";
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}



<dependencies>
    <dependency>
        <groupId>com.sparkjava</groupId>
        <artifactId>spark-core</artifactId>
        <version>2.9.3</version>
    </dependency>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.26</version>
    </dependency>
</dependencies>