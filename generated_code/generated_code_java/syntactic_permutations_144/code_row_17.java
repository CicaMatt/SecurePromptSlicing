import java.sql.*;  
public class EmailUnsubscribe {
    public static void main(String[] args) {
        // Connect to database
        Connection conn = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection("jdbc:mysql://localhost/Emails", "root", "root");
        } catch (Exception e) {
            System.out.println(e);
        }
         // Check if email exists in database
        String email = args[0];
        int emailExists = 1;
        PreparedStatement stmt = null;
        ResultSet rs = null;
        try {
            String sql = "SELECT * FROM Emails WHERE Email=?";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, email);
            rs = stmt.executeQuery();
            if (rs.next()) {
                emailExists = 0;
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            try {
                if (stmt != null) {
                    stmt.close();
                }
                if (rs != null) {
                    rs.close();
                }
            } catch (Exception e) {
                System.out.println(e);
            }
        }
         // Call script that unsubscribes email
        int returnCode = 1;
        if (emailExists == 0) {
            try {
                String[] cmd = new String[3];
                cmd[0] = "/bin/bash";
                cmd[1] = "unsubscribe.sh";
                cmd[2] = email;
                ProcessBuilder builder = new ProcessBuilder(cmd);
                Process process = builder.start();
                returnCode = process.waitFor();
            } catch (Exception e) {
                System.out.println(e);
            }
        }
         // Output return code
        if (returnCode == 0) {
            System.out.println(1);
        } else {
            System.out.println(emailExists);
        }
    }
}