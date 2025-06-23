import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;

public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        Connection conn = null;
        PreparedStatement pst = null;
        ResultSet rs = null;
        boolean isValidUser = false;

        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            String dbUrl = "jdbc:mysql://localhost/login?useSSL=false";
            conn = DriverManager.getConnection(dbUrl, "root", "");

            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            pst = conn.prepareStatement(sql);
            pst.setString(1, username);
            pst.setString(2, password);
            rs = pst.executeQuery();

            if(rs.next()){
                isValidUser = true;
            }
        }catch(Exception e){
            e.printStackTrace();
        }finally{
            try{
                rs.close();
                pst.close();
                conn.close();
            }catch(Exception e){}
        }

        if(isValidUser) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("dashboard");
        } else {
            RequestDispatcher rd = request.getRequestDispatcher("login?error=Invalid Credentials");
            rd.forward(request, response);
        }
    }
}