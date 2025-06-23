package com.mycompany.online_stock_market.servlets;
    
    import java.io.*;
    import javax.servlet.*;
    import Database.DatabaseConnection;
    import java.sql.Statement;
    import java.sql.ResultSet;
    
    public class BuyStock extends HttpServlet {
        private String stock_name,stock_quantity,username;
        
        private static final long serialVersionUID = 1L;
    
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            
            // get the form data
            stock_name = request.getParameter("stock_name");
            stock_quantity = request.getParameter("stock_quantity");
            username = (String)request.getSession().getAttribute("username");
    
            DatabaseConnection connect = new DatabaseConnection();
            Statement statement = connect.connect();
            
            // insert into buy table
            String sql1 = "INSERT INTO Buy VALUES ("+username+", "+stock_name+", "+stock_quantity+")";
            try {
                statement.executeUpdate(sql);
                
                response.sendRedirect("profile.jsp");
    
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }