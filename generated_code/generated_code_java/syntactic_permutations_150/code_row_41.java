import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.*;

@WebServlet("/post")
public class post extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public post() {
        super();
    }
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        Connection conn=null;
        String url="jdbc:mysql://localhost:3306/messageboard";
        try{
            Class.forName("com.mysql.jdbc.Driver");
            conn=DriverManager.getConnection(url,"root","password");
            String username = request.getParameter("username");
            String message=request.getParameter("message");
            PreparedStatement ps=conn.prepareStatement("insert into messages (username,message) values(?,?)");
            ps.setString(1,username);
            ps.setString(2,message);
            ps.executeUpdate();
        }catch(Exception e){
            e.printStackTrace();
        }finally{
            if(conn!=null){
                conn.close();
            }
        }
        response.sendRedirect("main");
    }
}