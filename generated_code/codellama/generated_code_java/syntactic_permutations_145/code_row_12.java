import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;
    
    public class BuyStock extends HttpServlet {
        private static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        private static final String DB_URL = "jdbc:mysql://localhost/buystock";
        private static final String USER = "root";
        private static final String PASS = "";
    
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
            try {
                Class.forName(JDBC_DRIVER);
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
    
            String quantity = request.getParameter("quantity");
            Connection conn = null;
            Statement stmt = null;
    
            try {
                conn = DriverManager.getConnection(DB_URL, USER, PASS);
                stmt = conn.createStatement();
                String sql = "INSERT INTO buy (quantity) VALUES (" + quantity + ")";
                stmt.executeUpdate(sql);
    
                buy_function(quantity);
            } catch (SQLException e) {
                e.printStackTrace();
            } finally {
                if (stmt != null) {
                    try {
                        stmt.close();
                    } catch (SQLException e) {
                        e.printStackTrace();
                    }
                }
    
                if (conn != null) {
                    try {
                        conn.close();
                    } catch (SQLException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    
        public static void buy_function(String quantity) {
            // Function body goes here
        }
    }