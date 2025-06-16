import java.sql.*;

public class Main {
  public static void main(String[] args) throws Exception {
    String url = "jdbc:sqlite:stocks.db";
    Connection con = DriverManager.getConnection(url);

    Statement stmt = con.createStatement();
    ResultSet rs = stmt.executeQuery("SELECT * FROM stocks");

    while (rs.next()) {
      String name = rs.getString("name");
      int quantity = rs.getInt("quantity");
      System.out.println(name + " - " + quantity);
    }
  }
}