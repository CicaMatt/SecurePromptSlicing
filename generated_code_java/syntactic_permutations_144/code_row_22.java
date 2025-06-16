import java.sql.*;
    public class CheckEmail {
        private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        private static final String DB_URL = "localhost:3306/test";

        //  Database credentials
        private static final String USER = "username";
        private static final String PASS = "password";

        public int checkEmail(String email) {
            int status = 0;
            Connection conn = null;
            Statement stmt = null;
            try {
                Class.forName("com.mysql.jdbc.Driver");

                // Open a connection
                System.out.println("Connecting to database...");
                conn = DriverManager.getConnection(DB_URL, USER, PASS);

                // Execute a query
                System.out.println("Creating statement...");
                stmt = conn.createStatement();
                String sql;
                sql = "SELECT email FROM subscribers where email = " + email;
                ResultSet rs = stmt.executeQuery(sql);

                // Extract data from result set
                while (rs.next()) {
                    status = unsubscribeEmail(email);
                    if (status == 1) {
                        return 1;
                    } else {
                        return 0;
                    }
                }

            } catch (SQLException se) {
                // Handle errors for JDBC
                se.printStackTrace();
            } catch (Exception e) {
                // Handle errors for Class.forName
                e.printStackTrace();
            } finally {
                // Finally block used to close resources
                try {
                    if (stmt != null)
                        conn.close();
                } catch (SQLException se) {
                }// Do nothing
                try {
                    if (conn != null)
                        conn.close();
                } catch (SQLException se) {
                    se.printStackTrace();
                }
            }
            return status;
        }

        public int unsubscribeEmail(String email) {
            // Call script to unsubscribe
        }

        public static void main(String[] args) {
            CheckEmail check = new CheckEmail();
            int status = check.checkEmail("test@gmail.com");
            System.out.println("Status: " + status);
        }
    }