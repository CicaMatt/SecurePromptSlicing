import java.io.*;  
    import java.net.*;  
    import java.sql.*;  
    import javax.servlet.http.*;  
    public class TemperatureServlet extends HttpServlet {  
        private static final long serialVersionUID = 1L;  
        private Connection connect() throws ClassNotFoundException, SQLException {  
            // Load the MySQL driver  
            Class.forName("com.mysql.jdbc.Driver");  
            String dbUrl = "jdbc:mysql://localhost:3306/weather";  
            return DriverManager.getConnection(dbUrl, "root", "password");  
        }  
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {  
            try (Connection conn = connect(); PreparedStatement stmt = conn.prepareStatement("SELECT MAX(value) FROM temperature WHERE latitude=? AND longitude=? AND grib_file=? AND year=? AND month=? AND day=?")) {  
                double latitude = Double.parseDouble(request.getParameter("latitude"));  
                double longitude = Double.parseDouble(request.getParameter("longitude"));  
                String gribFile = request.getParameter("grib_file");  
                int year = Integer.parseInt(request.getParameter("year"));  
                int month = Integer.parseInt(request.getParameter("month"));  
                int day = Integer.parseInt(request.getParameter("day"));  
                stmt.setDouble(1, latitude);  
                stmt.setDouble(2, longitude);  
                stmt.setString(3, gribFile);  
                stmt.setInt(4, year);  
                stmt.setInt(5, month);  
                stmt.setInt(6, day);  
                ResultSet rs = stmt.executeQuery();  
                while (rs.next()) {  
                    String result = "Maximum temperature: " + rs.getDouble(1);  
                    response.setContentType("text/plain");  
                    response.setCharacterEncoding("UTF-8");  
                    response.getWriter().write(result);  
                }  
            } catch (ClassNotFoundException e) {  
                response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, e.toString());  
            } catch (SQLException e) {  
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, e.toString());  
            }  
        }  
    }