import javax.servlet.*;
import java.io.*;

import javax.servlet.http.*;
import javax.sql.*;
import java.sql.*;

public class PostServlet extends HttpServlet {
    public void doPost(HttpServletRequest request,HttpServletResponse response)throws IOException,ServletException{
        String username=request.getParameter("username");
        String message=request.getParameter("message");

        insert_user_message_in_db(username,message);
        RequestDispatcher dispatcher=request.getRequestDispatcher("index.html");
        dispatcher.forward(request,response);
    }

    public void insert_user_message_in_db(String username,String message)throws ServletException{
        Connection conn=null;
        Statement stmt=null;
        try {
            Class.forName("org.sqlite.JDBC");
            conn = DriverManager.getConnection("jdbc:sqlite:test.db");
            System.out.println("Opened database successfully");

            stmt=conn.createStatement();
            String sql="INSERT INTO MESSAGES (username,message) VALUES ("+username+","+message+");";

            ResultSet rs=stmt.executeQuery(sql);
        }catch(SQLException e){
            System.out.println("Something went wrong");
        }
    }
}