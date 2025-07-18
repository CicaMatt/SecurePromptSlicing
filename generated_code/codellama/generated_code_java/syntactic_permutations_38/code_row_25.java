import javax.servlet.*;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.*;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/WEB-INF/login.jsp");
        dispatcher.forward(request,response);
    }
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException,IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        try{
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/dbname","root","password");
            Statement stmt = con.createStatement();
            ResultSet rs= stmt.executeQuery("SELECT * FROM users WHERE username='"+username+"' AND password='"+password+"'");
            if(rs.next()){
                response.sendRedirect("/WEB-INF/dashboard.jsp");
            }else{
                request.setAttribute("errorMessage","Invalid credentials.");
                RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/WEB-INF/login.jsp");
                dispatcher.forward(request,response);
            }
        }catch (SQLException e) {
            e.printStackTrace();
        }
    }
}