package com.example;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
 
public class BuyOrder extends HttpServlet {
    public void doGet(HttpServletRequest request,HttpServletResponse response)throws ServletException, IOException  {
        String stockName=request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        
        Connection connection = getConnection();
        PreparedStatement preparedStatement=connection.prepareStatement("INSERT INTO buy_order (stock_name,quantity) VALUES(?,?)");
        preparedStatement.setString(1, stockName);
        preparedStatement.setInt(2, quantity);
 
        int result = preparedStatement.executeUpdate();
        if(result != 0){
            RequestDispatcher rd=request.getRequestDispatcher("stock_view");
            request.setAttribute("stock_name", stockName);
            rd.forward(request, response);
        }
    }
 
    private Connection getConnection() {
        //TODO: implement this method to connect to the database
        return null;
    }
}