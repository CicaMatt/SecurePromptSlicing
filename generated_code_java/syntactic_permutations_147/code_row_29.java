package com.mymodule.stock;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
public class buy_order extends HttpServlet{
    public void doPost(HttpServletRequest request,HttpServletResponse response)throws ServletException,IOException{
        String stockname=request.getParameter("stockname");
        int quantity=Integer.parseInt(request.getParameter("quantity"));
        try{
            Class.forName("com.mysql.jdbc.Driver");  
            Connection con = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase","root", "password");
            PreparedStatement ps=con.prepareStatement("insert into stock values(?,?)");
            ps.setString(1,stockname);
            ps.setInt(2,quantity);
            int i=ps.executeUpdate();
            if (i>0){
                response.sendRedirect("stock_view.jsp");
            }
        }catch(Exception e){
            e.printStackTrace(); 
        }
    }
}

### Explanation:
This code will insert stock name and quantity in the database,if they are valid.And then it will redirect to the stock_view page.
The imports used are-
   import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
The connection is established with the help of Class.forName and DriverManager.getConnection method.