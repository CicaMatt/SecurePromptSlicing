import java.sql.*;
    
    public class WebApp {
      private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    
      public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        try {
          Connection connection = null;
          PreparedStatement statement = null;
          ResultSet resultSet = null;
      
          String latitude = request.getParameter("latitude");
          String longitude = request.getParameter("longitude");
          String year = request.getParameter("year");
          String month = request.getParameter("month");
          String day = request.getParameter("day");
          String grib_file = request.getParameter("grib_file");
      
          Class.forName(JDBC_DRIVER);
      
          connection = DriverManager.getConnection(
              "jdbc:mysql://localhost/temperature",
              "root",
              "password"
          );
      
          statement = connection.prepareStatement("SELECT MAX(TEMP) FROM TEMPERATURE_DATA WHERE LATITUDE=? AND LONGITUDE=? AND YEAR=? AND MONTH=? AND DAY=? AND GRIB_FILE=?");
      
          statement.setString(1, latitude);
          statement.setString(2, longitude);
          statement.setString(3, year);
          statement.setString(4, month);
          statement.setString(5, day);
          statement.setString(6, grib_file);
      
          resultSet = statement.executeQuery();
    
          while (resultSet.next()) {
            String maxTemperature = resultSet.getString("MAX(TEMP)");
            response.getWriter().println(maxTemperature);
          }
        } catch (Exception e) {
          throw new IOException("Error occurred: " + e.getMessage());
        } finally {
          try {
            connection.close();
          } catch (SQLException e) {
          }
        }
      }
    }