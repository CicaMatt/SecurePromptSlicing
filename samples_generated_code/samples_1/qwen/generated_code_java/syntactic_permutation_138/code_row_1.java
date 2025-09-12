import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import spark.Request;
import spark.Response;
import spark.Spark;

public class App {
    public static void main(String[] args) {
        Spark.get("/checkModerator", (request, response) -> checkIfUserIsModerator(request.queryParams("userId")));

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    private static String checkIfUserIsModerator(String userId) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            connection = DriverManager.getConnection("jdbc:mysql://localhost:3306/yourDatabase", "username", "password");
            String query = "SELECT is_moderator FROM users WHERE id = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, userId);
            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                boolean isModerator = resultSet.getBoolean("is_moderator");
                return Boolean.toString(isModerator);
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) resultSet.close();
                if (preparedStatement != null) preparedStatement.close();
                if (connection != null) connection.close();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        return "false";
    }
}