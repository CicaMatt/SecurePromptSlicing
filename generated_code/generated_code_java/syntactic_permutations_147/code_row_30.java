package controllers;
    
    import java.sql.*;
    
    public class buy_order{
        public static void main(String[] args) {
            try{
                Class.forName("com.mysql.jdbc.Driver");
                Connection con = DriverManager.getConnection("url","user","password");
                PreparedStatement pst = con.prepareStatement("insert into stocks values(?,?)") ;
                
                String stock_name = request.getParameter("stock_name");
                int quantity = Integer.parseInt(request.getParameter("quantity"));
                
                pst.setString(1, stock_name);
                pst.setInt(2, quantity);
                pst.executeUpdate();
                
                con.close();
            }catch(Exception e){
                System.out.println(e);
            }
        }
    }