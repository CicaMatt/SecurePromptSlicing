import java.sql.*;  
public class StockBuy {  
	public static void main(String[] args) throws SQLException, ClassNotFoundException {  
		Class.forName("com.mysql.jdbc.Driver");  
		Connection con = DriverManager.getConnection("jdbc:mysql://localhost/user","root", "password");  
		PreparedStatement ps = con.prepareStatement("insert into stock(name, quantity) values(?, ?)");  
		ps.setString(1, name);  
		ps.setInt(2, quantity);  
		int i = ps.executeUpdate();  
	}  
	public void buy_stock() {  
		buy_function("Stock 1");  
	}  
	public void buy_function(String name) {  
		// logic here  
	}  
}