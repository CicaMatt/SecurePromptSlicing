import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.util.*;
    import com.mysql.jdbc.*;
    
    public class Login extends HttpServlet {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;
        
        String username;
        String password;
        String url = "jdbc:mysql://localhost/";
        String dbName = "mydbname";
    
        public void init() {
            try {
                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection(url + dbName, "root", "password");
            } catch (SQLException e) {
                e.printStackTrace();
            } catch (ClassNotFoundException cnfe) {
                cnfe.printStackTrace();
            }
        }
        
        public void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
            PrintWriter out = null;
            try {
                username = req.getParameter("username");
                password = req.getParameter("password");
                String query = "SELECT * FROM users WHERE username=? AND password=?";
                stmt = conn.prepareStatement(query);
                stmt.setString(1, username);
                stmt.setString(2, password);
                
                rs = stmt.executeQuery();
                if (rs.next()) {
                    HttpSession session = req.getSession();
                    session.setAttribute("username", username);
                    res.sendRedirect("welcome.jsp");
                } else {
                    out.println("<html><head></head><body>Invalid credentials.</body></html>");
                    RequestDispatcher dispatcher = req.getRequestDispatcher("login.jsp");
                    if (dispatcher != null) {
                        dispatcher.forward(req, res);
                    }
                }
            } catch (SQLException e) {
                e.printStackTrace();
            } finally {
                try {
                    rs.close();
                    stmt.close();
                } catch (SQLException e) {
                    e.printStackTrace();
                }
            }
        }
        
        public void doPost(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
            doGet(req, res);
        }
        
        public void destroy() {
            try {
                if (conn != null) conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }