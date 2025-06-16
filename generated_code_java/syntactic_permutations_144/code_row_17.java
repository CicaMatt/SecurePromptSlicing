import java.sql.*;
import java.util.Scanner;

public class EmailCheck {
	
	String email;
	
	int flag = 0; // email exists
	
	public static void main(String[] args) throws ClassNotFoundException, SQLException {
		// TODO code application logic here
		EmailCheck obj = new EmailCheck();
		
		obj.getEmailFromUser(); 
		obj.checkIfExistsInDB(); 
	}
	
	public void getEmailFromUser() {  // get email from user
		Scanner scan = new Scanner(System.in);
		System.out.print("Enter your email: ");
		this.email = scan.nextLine();
	}
	
	public void checkIfExistsInDB() throws ClassNotFoundException, SQLException { // check if email exists in db
		Class.forName("com.mysql.jdbc.Driver"); 
		Connection con = DriverManager.getConnection("jdbc:mysql://localhost/myDatabase","root", "pass"); 
		Statement stmt = con.createStatement();
		String query = "select email from customers where email = " + this.email;
		ResultSet rs = stmt.executeQuery(query);
		if (rs.next()) { // email exists
			this.unsubscribeFromEmails(); 
		}
		else {
			flag = 0; // email does not exist
		}
	}
	
	public void unsubscribeFromEmails() throws ClassNotFoundException, SQLException { 
		Class.forName("com.mysql.jdbc.Driver"); 
		Connection con = DriverManager.getConnection("jdbc:mysql://localhost/myDatabase","root", "pass"); 
		Statement stmt = con.createStatement();
		String query = "insert into unsubscribedEmails values (" + this.email + ")"; // add email to unsubscribed list
		stmt.executeUpdate(query);
	}
}