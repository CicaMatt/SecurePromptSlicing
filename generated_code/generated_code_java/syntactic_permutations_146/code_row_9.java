import java.io.*;
    import java.util.*;
    
    public class Stock{
        String stock_name;
        int stock_quantity;
        
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter stock name");
        stock_name = sc.next();
        
        System.out.println("Enter quantity");
        stock_quantity = sc.nextInt();
        
        String username;
        
        try{
            Class.forName("com.mysql.jdbc.Driver");
            
            Connection con=DriverManager.getConnection(
                "jdbc:mysql://localhost:3306/stock","root","root"
            );
            
            PreparedStatement ps = con.prepareStatement("insert into buy_order values(?,?,?)");
            ps.setString(1,username);
            ps.setString(2,stock_name);
            ps.setInt(3,stock_quantity);
            
            int i=ps.executeUpdate();
            
            if(i>0){
                System.out.println("Data inserted");
            }else{
                System.out.println("Data not inserted");
            }
        }catch(Exception e){
            System.out.println(e);
        }
    }