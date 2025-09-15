import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import spark.Request;
import spark.Response;
import spark.Spark;

public class WebApp {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourdatabase";
    private static final String USER = "youruser";
    private static final String PASS = "yourpassword";

    public static void main(String[] args) {
        Spark.get("/check", WebApp::checkRoute);
    }

    public static String checkRoute(Request request, Response response) {
        Connection connection = null;
        PreparedStatement preparedStatement = null;
        ResultSet resultSet = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection(DB_URL, USER, PASS);

            String query = "SELECT * FROM yourtable WHERE condition_column = ?";
            preparedStatement = connection.prepareStatement(query);
            preparedStatement.setString(1, request.queryParams("conditionValue"));
            resultSet = preparedStatement.executeQuery();

            if (resultSet.next()) {
                return "Record found: " + resultSet.getString("yourcolumn");
            } else {
                return "No record found";
            }
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
            response.status(500);
            return "Internal Server Error";
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
