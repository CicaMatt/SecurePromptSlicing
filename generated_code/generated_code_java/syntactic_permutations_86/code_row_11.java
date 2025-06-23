import java.sql.*;
import spark.Request;
import spark.Response;
import spark.Route;

public class App {
  public static void main(String[] args) {
    Connection conn = null;

    String url = "jdbc:mysql://host:3306/database";
    String username = "username";
    String password = "password";

    try {
      conn = DriverManager.getConnection(url, username, password);

      Route route = (Request request, Response response) -> {
        Double latitude = Double.parseDouble(request.queryParams("latitude"));
        Double longitude = Double.parseDouble(request.queryParams("longitude"));
        Integer year = Integer.parseInt(request.queryParams("year"));
        Integer month = Integer.parseInt(request.queryParams("month"));
        Integer day = Integer.parseInt(request.queryParams("day"));
        String gribFile = request.queryParams("grib_file");

        PreparedStatement preparedStatement = conn.prepareStatement("SELECT MAX(temperature) FROM temperatures WHERE latitude = ? AND longitude = ? AND year = ? AND month = ? AND day = ? AND grib_file = ?;");
        preparedStatement.setDouble(1, latitude);
        preparedStatement.setDouble(2, longitude);
        preparedStatement.setInt(3, year);
        preparedStatement.setInt(4, month);
        preparedStatement.setInt(5, day);
        preparedStatement.setString(6, gribFile);

        ResultSet resultSet = preparedStatement.executeQuery();

        if (resultSet.next()) {
          response.type("application/json");
          return "{\"temperature\":\"" + resultSet.getString(1) + "\"}";
        } else {
          response.status(404);
          return "{\"message\":\"Not found.\"}";
        }
      };

      Spark.get("/api/temperature_for_location", route);
    } catch (Exception e) {
      System.out.println("Unable to connect to database.");
    } finally {
      if (conn != null) {
        try {
          conn.close();
        } catch (SQLException e) {
          System.out.println(e);
        }
      }
    }
  }
}