import java.io.*;
    import javax.servlet.ServletException;
    import javax.servlet.http.HttpServlet;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    import java.sql.Connection;
    import java.sql.DriverManager;
    import java.sql.ResultSet;
    import java.sql.Statement;

    public class Login extends HttpServlet {

        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");

            if (checkLogin(username, password)) {
                // Redirect to home page
            } else {
                // Redirect to login page
            }
        }

        public boolean checkLogin(String username, String password) throws ServletException, IOException {
            Connection conn = null;
            Statement stmt = null;
            ResultSet rs = null;
            try {
                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection(
                    "jdbc:mysql://localhost/mydb", "username", "password");
                stmt = conn.createStatement();
                rs = stmt.executeQuery("SELECT * FROM users WHERE username='" +
                    username + "' AND password='" + password + "'");

                if (rs.next()) {
                    return true;
                } else {
                    return false;
                }
            } catch (Exception e) {
                throw new ServletException(e);
            } finally {
                try {
                    rs.close();
                    stmt.close();
                    conn.close();
                } catch (Exception e) {
                    // Ignore
                }
            }
        }
    }