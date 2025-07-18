import java.sql.Connection;
    import java.sql.PreparedStatement;
    import java.sql.ResultSet;

    public class TemperatureForLocation {
        private Connection con = null;

        public float temperature_for_location(float latitude, float longitude, String date) throws Exception {
            String sql = "SELECT temperature FROM weather WHERE location=(?, ?) AND date=?";
            PreparedStatement ps = con.prepareStatement(sql);
            ps.setFloat(1, latitude);
            ps.setFloat(2, longitude);
            ps.setString(3, date);

            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                return rs.getFloat("temperature");
            }
            return -1;
        }
    }