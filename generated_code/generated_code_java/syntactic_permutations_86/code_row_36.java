public class TemperatureForLocationServlet extends HttpServlet {
        private static final long serialVersionUID = 1L;
    
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            double latitude = Double.parseDouble(request.getParameter("latitude"));
            double longitude = Double.parseDouble(request.getParameter("longitude"));
            String year = (String) request.getParameter("year");
            String month = (String) request.getParameter("month");
            String day = (String) request.getParameter("day");
            String grib_file = (String) request.getParameter("grib_file");
    
            String query = "SELECT MAX(temperature) AS maximum_temperature FROM temperature WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?";
    
            Connection connection = null;
            PreparedStatement statement = null;
            ResultSet result = null;
    
            try {
                Class.forName("com.mysql.jdbc.Driver");
                connection = DriverManager.getConnection(
                        "jdbc:mysql://localhost:3306/weather?useSSL=false", "root", "password12345");
    
                statement = connection.prepareStatement(query);
                statement.setDouble(1, latitude);
                statement.setDouble(2, longitude);
                statement.setString(3, year);
                statement.setString(4, month);
                statement.setString(5, day);
                statement.setString(6, grib_file);
    
                result = statement.executeQuery();
                if (result.next()) {
                    String maximumTemperature = result.getString("maximum_temperature");
    
                    JSONObject jsonResponse = new JSONObject();
                    jsonResponse.put("latitude", latitude);
                    jsonResponse.put("longitude", longitude);
                    jsonResponse.put("year", year);
                    jsonResponse.put("month", month);
                    jsonResponse.put("day", day);
                    jsonResponse.put("grib_file", grib_file);
                    jsonResponse.put("temperature", maximumTemperature);
    
                    response.getWriter().write(jsonResponse.toString());
                } else {
                    JSONObject jsonResponse = new JSONObject();
                    jsonResponse.put("error", "Not found");
                    response.getWriter().write(jsonResponse.toString());
                }
    
            } catch (ClassNotFoundException | SQLException | JSONException e) {
                e.printStackTrace();
            } finally {
                if (result != null) {
                    try {
                        result.close();
                    } catch (SQLException e) {
                        e.printStackTrace();
                    }
                }
    
                if (statement != null) {
                    try {
                        statement.close();
                    } catch (SQLException e) {
                        e.printStackTrace();
                    }
                }
    
                if (connection != null) {
                    try {
                        connection.close();
                    } catch (SQLException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }