package myPackage;

    import java.io.*;
    import java.sql.*;
    import javax.imageio.ImageIO;

    public class SaveImage {
        private static final String DB_URL = "jdbc:mysql://localhost/myDatabase";
        private static final String USERNAME = "root";
        private static final String PASSWORD = "password123";
        private static final int BUFFER = 8192;

        public void saveImage(String fileName, byte[] image) {
            Connection conn = null;
            PreparedStatement stmt = null;

            try {
                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection(DB_URL, USERNAME, PASSWORD);
                String sql = "INSERT INTO images (name, data) VALUES(?, ?)";
                stmt = conn.prepareStatement(sql);
                stmt.setString(1, fileName);
                stmt.setBytes(2, image);
                int rowsAffected = stmt.executeUpdate();
            } catch (Exception e) {
                throw new RuntimeException(e);
            } finally {
                if (stmt != null) try { stmt.close(); } catch (SQLException ignored) {}
                if (conn != null) try { conn.close(); } catch (SQLException ignored) {}
            }
        }
    }