import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class TemperatureServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    // Connect to the MySQL database using JDBC
    String url = "jdbc:mysql://localhost/weather_db";
    String user = "root";
    String password = "password";
    Connection conn;
    try {
      conn = DriverManager.getConnection(url, user, password);
    } catch (SQLException e) {
      throw new ServletException("Connection could not be established", e);
    }
    
    // Get the parameters from the request URL
    String latitude = request.getParameter("latitude");
    String longitude = request.getParameter("longitude");
    String month = request.getParameter("month");
    String day = request.getParameter("day");
    String grib_file = request.getParameter("grib_file");
    
    // Build the SQL query
    String sql = "SELECT MAX(temperature) FROM weather_data WHERE latitude=" + latitude + " AND longitude=" + longitude + " AND month=" + month + " AND day=" + day + " AND grib_file='" + grib_file + "'";
    
    // Execute the query and store the result
    ResultSet rs;
    try {
      Statement stmt = conn.createStatement();
      rs = stmt.executeQuery(sql);
    } catch (SQLException e) {
      throw new ServletException("Query could not be executed", e);
    }
    
    // Output the result as JSON
    response.setContentType("application/json");
    PrintWriter out = response.getWriter();
    if (rs.next()) {
      int max_temperature = rs.getInt(1);
      String json = "{ \"max_temperature\": " + max_temperature + " }";
      out.print(json);
    } else {
      String json = "{ \"error\": \"No data found\" }";
      out.print(json);
    }
    
    // Close the connection to the MySQL database
    try {
      conn.close();
    } catch (SQLException e) {
      throw new ServletException("Connection could not be closed", e);
    }
  }
}