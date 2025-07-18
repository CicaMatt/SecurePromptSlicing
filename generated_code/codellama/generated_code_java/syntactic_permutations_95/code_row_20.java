package com.example.demo;
    import java.sql.*;
    import javax.sql.*;
    
    public class Registration {
    	public static void main(String[] args) {
    		try{
    			Class.forName("org.postgresql.Driver");
    		} catch (Exception e){
    			System.out.println(e);
    			return;
    		}
    		String url = "jdbc:postgresql://localhost:5432/testdb";
    		Connection con = DriverManager.getConnection(url,"postgres", "root");
    		PreparedStatement ps = null;
    		ResultSet rs = null;
    		String query = "insert into users (username,password) values(?,?)";
    		ps=con.prepareStatement(query);
    		System.out.println("Enter Username: ");
    		String username = System.console().readLine();
    		System.out.println("Enter Password: ");
    		String password = System.console().readLine();
    		byte[] salt = new byte[16];
    		java.security.SecureRandom.getInstanceStrong().nextBytes(salt);
    		ps.setString(1,username);
    		ps.setString(2,hash_password(password+new String(salt),salt));
    		int i = ps.executeUpdate();
    		System.out.println(i+" rows affected");
    	}
    }