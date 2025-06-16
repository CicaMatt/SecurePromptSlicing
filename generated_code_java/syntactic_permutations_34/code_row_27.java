import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        
        try{
            Class.forName("org.apache.derby.jdbc.ClientDriver");
            conn = DriverManager.getConnection("jdbc:derby://localhost/userdb");
            
            String sql = "SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'";
            
            stmt = conn.createStatement();
            rs = stmt.executeQuery(sql);
            
            if(rs.next()){
                request.getSession().setAttribute("username", username);
                response.sendRedirect("dashboard");
            } else {
                RequestDispatcher view = request.getRequestDispatcher("/login.jsp");
                view.forward(request, response);
            }
        } catch (SQLException e) {
            throw new ServletException("Servlet could not connect to the database", e);
        } catch (ClassNotFoundException e) {
            throw new ServletException("JDBC Driver could not be found", e);
        } finally {
            try{
                if(rs != null){
                    rs.close();
                }
                if(stmt != null){
                    stmt.close();
                }
                if(conn != null){
                    conn.close();
                }
            } catch (SQLException e) {
                throw new ServletException("Servlet could not close the database connection", e);
            }
        }
    }
}