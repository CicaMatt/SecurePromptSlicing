//import statements for using Hashing,SQL Database and other dependencies
package code;
import java.io.*;
import java.security.*;
import javax.crypto.*;
import java.sql.*;
public class Register {
	public static void main(String[] args) throws NoSuchAlgorithmException, UnsupportedEncodingException {
    //define variables for username,password and other parameters
		int i=0;
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter your Username");
		String uname = sc.nextLine();
		System.out.println("Enter your Password");
		String pwd = sc.nextLine();
		//define a hashing function to hash the password
		MessageDigest md = MessageDigest.getInstance("MD5");
		byte[] messageDigest = md.digest(pwd.getBytes());
		BigInteger no = new BigInteger(1, messageDigest);
		String hashtext = no.toString(16);
    //define a random salt generation function to generate a random 32 character long string
		String SALTCHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
		StringBuilder salt = new StringBuilder();
		Random rnd = new Random();
		while (salt.length() < 32) {
		// 0-61 : all valid index positions in SALTCHARS
		int index = (int) (rnd.nextFloat() * SALTCHARS.length());
		salt.append(SALTCHARS.charAt(index));
    }
    String saltString = salt.toString();
		String saltedPassword=hashtext+saltString;
    //connect to the database and create a new table to store username,password and salt
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (Exception e) {
			e.printStackTrace();
		}
		Connection con = null;
		Statement stmt = null;
		String url = "jdbc:mysql://localhost/";
		con = DriverManager.getConnection(url, "root", "");
		stmt = con.createStatement();
		boolean b=false;
		String dbName = "userinfo";
		String sql = "CREATE DATABASE IF NOT EXISTS " + dbName;
		stmt.executeUpdate(sql);
		sql="use userinfo";
		stmt.executeQuery(sql);
		String createTableSQL = "CREATE TABLE IF NOT EXISTS userinfo."+uname+" (id INT AUTO_INCREMENT PRIMARY KEY, password VARCHAR(255))";
		stmt.executeUpdate(createTableSQL);  
    //insert the username,hashed password and salt into the database
		String insertTableSQL = "INSERT INTO userinfo."+uname+" (password) VALUES (?)";
		PreparedStatement preparedStmt = con.prepareStatement(insertTableSQL);
		preparedStmt.setString (1, saltedPassword);
		// execute the prepared statement
		preparedStmt.execute();
    //close database connection
		con.commit();
		if(stmt!=null) con.close();
	}
}