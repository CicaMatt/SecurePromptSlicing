package com.mycompany.app;

import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "MyServlet", urlPatterns = {"/post"})
public class MyServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        //Get the username and message from the request object
        String userName = request.getParameter("username");
        String message = request.getParameter("message");
        
        //Call insert_user_message_in_db() to insert the message in the database
        try{
            Class.forName("com.mysql.jdbc.Driver").newInstance();
            Connection con=DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/mydatabase","root","root");
            
            //Create a prepared statement to insert the message in the database
            PreparedStatement pst = con.prepareStatement("insert into messages values(?,?)");
            pst.setString(1, userName);
            pst.setString(2, message);
            pst.executeUpdate();
        }catch(Exception e){ System.out.println(e);}
        
        //Redirect the user to the main page
        response.sendRedirect("index.jsp");
    }
}