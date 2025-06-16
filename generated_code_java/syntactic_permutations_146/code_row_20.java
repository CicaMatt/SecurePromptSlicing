import java.sql.*;  
public class StockBuy {    
    public static void main(String[] args) {       
        String stock_name = "IBM";       
        int stock_quantity = 10;       
        String username = "John Doe";        
        // Create a variable for the connection string.       
        String connectionUrl = "jdbc:sqlserver://<server>:<port>;databaseName=stockdb;user=<username>;password=<password>;";     
        try {          
            // Load the JDBC driver.         
            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");      
            // Create a connection object.        
            Connection con = DriverManager.getConnection(connectionUrl);        
            Statement stmt = con.createStatement();          
            String sqlInsert;         
            sqlInsert = "INSERT INTO buyorder (stock_name, stock_quantity, username) values ('" + stock_name + "', " + stock_quantity + ", '" + username + "')";          
            int result = stmt.executeUpdate(sqlInsert);          
            if (result > 0) {            
                System.out.println("Data is inserted successfully into the database.");         
            } else {            
                System.out.println("There was a problem inserting the data." + "\n" + "Please try again!");         
            }        
        } catch (Exception e) {          
            e.printStackTrace();        
        }    
    }  
}