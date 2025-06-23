import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class Login extends HttpServlet {
    
    private String dbUrl = "jdbc:mysql://localhost/userdb";
    private String dbUser = "myuser";
    private String dbPass = "password";
    private Connection conn;
    
    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(dbUrl, dbUser, dbPass);
        } catch (SQLException e) {
            throw new ServletException(e);
        } catch (ClassNotFoundException e) {
            throw new ServletException(e);
        }
    }
    
    public void destroy() throws ServletException {
        try {
            conn.close();
        } catch (SQLException e) {
            throw new ServletException(e);
        }
    }
    
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String email = req.getParameter("email");
        String passwd = req.getParameter("passwd");
        
        if (email == null || passwd == null) {
            RequestDispatcher rd = req.getRequestDispatcher("/login.jsp");
            rd.forward(req, resp);
            
        } else {
            try {
                PreparedStatement ps = conn.prepareStatement("SELECT * FROM users WHERE email=? and passwd=?");
                ps.setString(1, email);
                ps.setString(2, passwd);
                
                ResultSet rs = ps.executeQuery();
                
                if (rs.next()) {
                    HttpSession session = req.getSession();
                    session.setAttribute("userid", rs.getString("userid"));
                    
                    String userType = rs.getString("usertype");
                    if (userType == "admin") {
                        RequestDispatcher rd = req.getRequestDispatcher("/admin.jsp");
                        rd.forward(req, resp);
                        
                    } else {
                        RequestDispatcher rd = req.getRequestDispatcher("/user.jsp");
                        rd.forward(req, resp);
                    }
                } else {
                    RequestDispatcher rd = req.getRequestDispatcher("/login.jsp");
                    rd.forward(req, resp);
                }
            } catch (SQLException e) {
                throw new ServletException(e);
            }
        }
    }
}