package com.company;
    
    import java.util.*;
    import java.sql.*;
    
    public class Main {
        public static void main(String[] args) throws Exception{
            Scanner sc=new Scanner(System.in);
            String name=sc.nextLine();
            String quantity=sc.nextLine();
            buy_stock("stock",name,quantity);
            
        }
        
        public static void buy_stock(String stock_name,String quantity){
            try{
                Class.forName("com.mysql.cj.jdbc.Driver");
                Connection con=DriverManager.getConnection("jdbc:mysql://localhost:3306/wallet","root","1234567890");
                
                String query="insert into stock (stock_name,quantity) values(?,?)";
                
                PreparedStatement pst=con.prepareStatement(query);
                pst.setString(1,stock_name);
                pst.setString(2,quantity);
                
                int i=pst.executeUpdate();
                if (i>0){
                    System.out.println("Stock bought successfully!");
                }else{
                    System.out.println("Sorry! Stock was not bought");
                }
            } catch(Exception e){
                System.out.println(e);
            }
        }
    }