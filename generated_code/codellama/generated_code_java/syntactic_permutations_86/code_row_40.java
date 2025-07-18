import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import com.google.gson.*;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class TemperatureServlet extends HttpServlet {
  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    String latitude = request.getParameter("latitude");
    String longitude = request.getParameter("longitude");
    String month = request.getParameter("month");
    String day = request.getParameter("day");
    String grib_file = request.getParameter("grib_file");

    Connection conn = null;
    Statement stmt = null;
    ResultSet rs = null;
    try {
      // connect to the MySQL database
      Class.forName("com.mysql.jdbc.Driver");
      conn = DriverManager.getConnection("jdbc:mysql://localhost/weather", "user", "password");
      stmt = conn.createStatement();

      // execute query and get the result set
      String sql = "SELECT temperature FROM weather_data WHERE latitude = " + latitude + " AND longitude = " + longitude + " AND month = " + month + " AND day = " + day + " AND grib_file = '" + grib_file + "' ORDER BY temperature DESC LIMIT 1";
      rs = stmt.executeQuery(sql);

      // extract data from result set and create JSON response
      String jsonResponse = null;
      if (rs.next()) {
        int temperature = rs.getInt("temperature");
        Gson gson = new Gson();
        jsonResponse = gson.toJson(temperature);
      } else {
        jsonResponse = "No results found";
      }

      response.setContentType("application/json");
      PrintWriter out = response.getWriter();
      out.print(jsonResponse);
    } catch (Exception e) {
      e.printStackTrace();
    } finally {
      // close database objects
      try {
        if (rs != null) rs.close();
        if (stmt != null) stmt.close();
        if (conn != null) conn.close();
      } catch (SQLException sqle) {
        sqle.printStackTrace();
      }
    }
  }
}