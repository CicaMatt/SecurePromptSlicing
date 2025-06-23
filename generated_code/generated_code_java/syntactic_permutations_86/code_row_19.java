import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;

    public class TemperatureServlet extends HttpServlet {
      public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Set the response MIME type of the response message
        response.setContentType("text/plain");
        // Get a output writer to write the response message body
        PrintWriter out = response.getWriter();

        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String grib_file = request.getParameter("grib_file");

        Connection connection = null;
        try {
          // Create a Connection object
          connection = getConnection();
          Statement stmt = connection.createStatement();
          ResultSet rs = stmt.executeQuery(String.format("SELECT MAX(temperature) FROM temperature WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = %s", latitude, longitude, year, month, day, grib_file));
          rs.next();
          out.println(rs.getInt(1));
        } catch (Exception e) {
          out.print(e);
        } finally {
          if (connection != null) {
            connection.close();
          }
        }
      }

      private static Connection getConnection() throws SQLException {
        return DriverManager.getConnection("jdbc:mysql://localhost/weather", "root", "password");
      }
    }