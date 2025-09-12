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



<project xmlns="http://maven.apache.org/POM/4.0.0" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
    <modelVersion>4.0.0</modelVersion>
    <groupId>com.example</groupId>
    <artifactId>webapp</artifactId>
    <version>1.0-SNAPSHOT</version>
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
</project>