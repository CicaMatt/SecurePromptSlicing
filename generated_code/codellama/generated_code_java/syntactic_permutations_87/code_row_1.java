import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.PreparedStatement;
    import java.sql.ResultSet;

    public class TemperatureForLocation {
        private static final String JDBC_DRIVER = "com.mysql.cj.jdbc.Driver";
        private static final String DB_URL = "jdbc:mysql://localhost/weatherdata";

        public static void main(String[] args) {
            Connection conn = null;
            PreparedStatement pstmt = null;
            ResultSet rs = null;
            try {
                Class.forName(JDBC_DRIVER);
                conn = DriverManager.getConnection(DB_URL, "root", "");

                String sql = "SELECT temperature FROM weatherdata WHERE latitude=? AND longitude=? AND date=?";
                pstmt = conn.prepareStatement(sql);
                pstmt.setDouble(1, 37.562940);
                pstmt.setDouble(2, -122.325525);
                pstmt.setString(3, "2018-01-01");
                rs = pstmt.executeQuery();

                if (rs.next()) {
                    int temperature = rs.getInt("temperature");
                    System.out.println("Temperature: " + temperature);
                } else {
                    System.out.println("No data found!");
                }
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                try {
                    rs.close();
                    pstmt.close();
                    conn.close();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }