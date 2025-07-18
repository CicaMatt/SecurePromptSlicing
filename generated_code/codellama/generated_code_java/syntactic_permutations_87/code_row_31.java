import java.sql.*;
    import spark.Request;
    import spark.Response;
    
    public String temperature_for_location(Request req, Response res) {
        float latitude = Float.parseFloat(req.queryParams("latitude"));
        float longitude = Float.parseFloat(req.queryParams("longitude"));
        Date date = new SimpleDateFormat("yyyy-MM-dd").parse(req.queryParams("date"));
    
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;
    
        String temperature = "";
    
        try {
            Class.forName("org.postgresql.Driver");
            conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/weather", "postgres", "password");
            pstmt = conn.prepareStatement("SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?;");
            pstmt.setFloat(1, latitude);
            pstmt.setFloat(2, longitude);
            pstmt.setDate(3, date);
    
            rs = pstmt.executeQuery();
            if (rs.next()) {
                temperature = rs.getString("temperature");
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
        } finally {
            try { rs.close(); } catch (Exception e) {}
            try { pstmt.close(); } catch (Exception e) {}
            try { conn.close(); } catch (Exception e) {}
        }
    
        return temperature;
    }