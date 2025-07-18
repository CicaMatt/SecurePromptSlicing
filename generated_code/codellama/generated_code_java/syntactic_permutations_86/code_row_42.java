import java.sql.*;
import javax.servlet.http.*;
import org.json.JSONObject;
public class TemperatureServlet extends HttpServlet {
  Connection conn = null;
  PreparedStatement stmt = null;
  ResultSet rs = null;
  public void init(ServletConfig config) throws ServletException {
    try {
      Class.forName("com.mysql.jdbc.Driver");
      String url = "jdbc:mysql://<database-host>:3306/weather";
      conn = DriverManager.getConnection(url, "<username>", "<password>");
    } catch (Exception e) {
      throw new ServletException("Error connecting to database.");
    }
  }
  public void doGet(HttpServletRequest req, HttpServletResponse resp)
                                   throws IOException, ServletException {
    try {
      double latitude = Double.parseDouble(req.getParameter("latitude"));
      double longitude = Double.parseDouble(req.getParameter("longitude"));
      int year = Integer.parseInt(req.getParameter("year"));
      int month = Integer.parseInt(req.getParameter("month"));
      String query = "SELECT MAX(temperature) FROM weather_data WHERE " +
                     "latitude = ? AND longitude = ? AND YEAR(date) = ? " +
                     "AND MONTH(date) = ?";
      stmt = conn.prepareStatement(query);
      stmt.setDouble(1, latitude);
      stmt.setDouble(2, longitude);
      stmt.setInt(3, year);
      stmt.setInt(4, month);
      rs = stmt.executeQuery();
      if (rs.next()) {
        double maxTemperature = rs.getDouble(1);
        JSONObject json = new JSONObject("{'max_temperature': " +
                                         String.valueOf(maxTemperature) + "}");
        resp.setContentType("application/json");
        resp.getWriter().println(json.toString());
      } else {
        throw new ServletException("No data found.");
      }
    } catch (Exception e) {
      throw new ServletException("Error querying the database.");
    } finally {
      if (rs != null) rs.close();
      if (stmt != null) stmt.close();
      if (conn != null) conn.close();
    }
  }
}