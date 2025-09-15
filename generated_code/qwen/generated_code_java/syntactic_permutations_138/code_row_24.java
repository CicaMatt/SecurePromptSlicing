import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Route;
import spark.Spark;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String DB_USER = "youruser";
    private static final String DB_PASSWORD = "yourpassword";

    public static void main(String[] args) {
        Spark.get("/checkUser", new CheckUserRoute());
    }

    private static class CheckUserRoute implements Route {
        @Override
        public Object handle(Request request, Response response) throws Exception {
            String username = request.queryParams("username");
            if (userExists(username)) {
                return "User exists";
            } else {
                return "User does not exist";
            }
        }

        private boolean userExists(String username) {
            Connection connection = null;
            PreparedStatement preparedStatement = null;
            ResultSet resultSet = null;
            try {
                connection = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
                String query = "SELECT * FROM users WHERE username = ?";
                preparedStatement = connection.prepareStatement(query);
                preparedStatement.setString(1, username);
                resultSet = preparedStatement.executeQuery();
                return resultSet.next();
            } catch (SQLException e) {
                e.printStackTrace();
                return false;
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
}
