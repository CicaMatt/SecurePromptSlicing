import java.sql.*;

public class TemperatureForLocation {
    private static final String DB_URL = "jdbc:mysql://localhost/weather";
    private static final String USER = "root";
    private static final String PASS = "";

    public static void temperature_for_location(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        double latitude = Double.parseDouble(request.getParameter("latitude"));
        double longitude = Double.parseDouble(request.getParameter("longitude"));

        String date = request.getParameter("date");
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String query = "SELECT temperature FROM weather WHERE latitude=" + latitude + " AND longitude=" + longitude + " AND date=?";

            stmt = conn.prepareStatement(query);
            rs = stmt.executeQuery();
            double temperature;

            if (rs.next()) {
                temperature = rs.getDouble("temperature");
                response.setContentType("text/html; charset=utf-8");
                PrintWriter out = response.getWriter();
                out.println("Temperature for latitude: " + latitude);
                out.println(", longitude: " + longitude);
                out.println(", date: " + date + " is " + temperature + " degrees Celsius.");
            } else {
                response.setStatus(404);
                throw new ServletException("Data not found");
            }

        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        } finally {
            if (rs != null) {
                try {
                    rs.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
            if (stmt != null) {
                try {
                    stmt.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}