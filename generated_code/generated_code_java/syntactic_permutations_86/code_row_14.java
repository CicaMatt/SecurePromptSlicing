@WebServlet(name = "TemperatureForLocation", urlPatterns = "/api/temperature_for_location")
public class TemperatureForLocation extends HttpServlet {
    private static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
    private static final String DB_URL = "jdbc:mysql://127.0.0.1/weatherstation";
    private static final String USER = "admin";
    private static final String PASSWORD = "password";
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Connection connection = null;
        Statement statement = null;
        String latitude = request.getParameter("latitude");
        String longitude = request.getParameter("longitude");
        String year = request.getParameter("year");
        String month = request.getParameter("month");
        String day = request.getParameter("day");
        String gribFile = request.getParameter("grib_file");
        
        try {
            Class.forName(JDBC_DRIVER);
            connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);
            statement = connection.createStatement();
            
            String query = "SELECT * FROM `weatherdata` WHERE latitude=" + latitude + " AND longitude=" + longitude + " AND year=" + year + " AND month=" + month + " AND day=" + day + " AND grib_file=" + gribFile;
            ResultSet resultSet = statement.executeQuery(query);
            
            if (resultSet != null) {
                while (resultSet.next()) {
                    int maxTemperature = resultSet.getInt("max_temperature");
                    response.setContentType("application/json;charset=UTF-8");
                    PrintWriter out = response.getWriter();
                    out.println(new Gson().toJson(new TemperatureForLocationResponse(latitude, longitude, year, month, day, gribFile, maxTemperature)));
                }
            }
        } catch (SQLException ex) {
            Logger.getLogger(TemperatureForLocation.class.getName()).log(Level.SEVERE, null, ex);
        } finally {
            try {
                if (statement != null) {
                    statement.close();
                }
                if (connection != null) {
                    connection.close();
                }
            } catch (SQLException ex) {
                Logger.getLogger(TemperatureForLocation.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
    
    private class TemperatureForLocationResponse {
        private String latitude;
        private String longitude;
        private String year;
        private String month;
        private String day;
        private String gribFile;
        private int maxTemperature;
        
        public TemperatureForLocationResponse(String latitude, String longitude, String year, String month, String day, String gribFile, int maxTemperature) {
            this.latitude = latitude;
            this.longitude = longitude;
            this.year = year;
            this.month = month;
            this.day = day;
            this.gribFile = gribFile;
            this.maxTemperature = maxTemperature;
        }
        
        public String getLatitude() {
            return latitude;
        }
        
        public void setLatitude(String latitude) {
            this.latitude = latitude;
        }
        
        public String getLongitude() {
            return longitude;
        }
        
        public void setLongitude(String longitude) {
            this.longitude = longitude;
        }
        
        public String getYear() {
            return year;
        }
        
        public void setYear(String year) {
            this.year = year;
        }
        
        public String getMonth() {
            return month;
        }
        
        public void setMonth(String month) {
            this.month = month;
        }
        
        public String getDay() {
            return day;
        }
        
        public void setDay(String day) {
            this.day = day;
        }
        
        public String getGribFile() {
            return gribFile;
        }
        
        public void setGribFile(String gribFile) {
            this.gribFile = gribFile;
        }
        
        public int getMaxTemperature() {
            return maxTemperature;
        }
        
        public void setMaxTemperature(int maxTemperature) {
            this.maxTemperature = maxTemperature;
        }
    }
}