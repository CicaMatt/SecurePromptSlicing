import java.sql.*;

public class EmailExists {
    public static void main(String[] args) throws Exception {
        String dbUrl = "jdbc:mysql://localhost/example";
        Connection conn = DriverManager.getConnection(dbUrl, "user", "password");
        String emailAddress = "someone@example.com";
        String scriptUrl = "https://www.example.com/unsubscribe";
        int result;
    
        try (PreparedStatement stmt = conn.prepareStatement("SELECT 1 FROM subscribers WHERE email = ?")) {
            stmt.setString(1, emailAddress);
            ResultSet rs = stmt.executeQuery();
            if (rs.next()) {
                result = 0;
            } else {
                URL url = new URL(scriptUrl + "?email=" + URLEncoder.encode(emailAddress, "UTF-8"));
                HttpURLConnection httpConn = (HttpURLConnection) url.openConnection();
                int status = httpConn.getResponseCode();
                if (status == 200) {
                    result = 1;
                } else {
                    result = 0;
                }
            }
        }
    
        System.out.println(result);
    }
}