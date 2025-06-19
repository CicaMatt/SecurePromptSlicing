import java.sql.*;

public class BuyOrder{
	public void buy_order(String stkname, int quantity){
		try {
			Class.forName("com.mysql.cj.jdbc.Driver");
			Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/stock", "root", "password");

			PreparedStatement ps=con.prepareStatement("insert into stock values(?,?)");
			ps.setString(1, stkname);
			ps.setInt(2, quantity);

			int i = ps.executeUpdate();
			if (i > 0) {
			    System.out.println("Data inserted successfully");
			}
		} catch (Exception e) {
			System.out.println(e);
		}
	}
}