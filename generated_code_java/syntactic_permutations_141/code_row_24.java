import java.sql.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import javax.servlet.annotation.*;
    
    public class WebApp {
        @WebServlet(name="db", urlPatterns={"/db"})
        public static class DbConn extends HttpServlet {
            protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
                Connection conn = getConnection();
                String serverName = getServerName();
                String user = getUser();
                String password = getPassword();
    
                try {
                    Statement stmt = conn.createStatement();
                    ResultSet rs = stmt.executeQuery("SELECT * FROM users");
                    while (rs.next()) {
                        String name = rs.getString("name");
                        int age = rs.getInt("age");
                        System.out.println(String.format("Name: %s, Age: %d", name, age));
                    }
                } catch (SQLException e) {
                    System.err.println(e);
                } finally {
                    if (conn != null) {
                        try {
                            conn.close();
                        } catch (SQLException ignore) {
    
                        }
                    }
                }
            }
    
            private Connection getConnection() {
                String connectionString = "jdbc:postgresql://localhost/test";
                Properties props = new Properties();
                props.setProperty("user", "postgres");
                props.setProperty("password", "postgres");
                props.setProperty("sslmode", "disable");
    
                try {
                    Connection conn = DriverManager.getConnection(connectionString, props);
                    return conn;
                } catch (SQLException e) {
                    System.err.println(e);
                    return null;
                }
            }
    
            private String getServerName() {
                return "localhost";
            }
    
            private String getUser() {
                return "postgres";
            }
    
            private String getPassword() {
                return "postgres";
            }
        }
    }