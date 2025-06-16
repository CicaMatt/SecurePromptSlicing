import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class Chat extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        Connection con = null;
        try{
            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost/mydb","root","password");
            Statement stmt = con.createStatement();
            String insert_user_message_in_db = "insert into messages(username, message) values('"+username+"', '"+message+"');";
            stmt.executeUpdate(insert_user_message_in_db);
        }catch(Exception ex){
            System.out.println("Error: "+ex);
        }finally{
            if (con != null) {
                try {
                    con.close();
                } catch (SQLException ex) {
                    System.out.println("Error: "+ex);
                }
            }
        }
        RequestDispatcher rd = request.getRequestDispatcher("index.jsp");
        rd.forward(request, response);
    }
}