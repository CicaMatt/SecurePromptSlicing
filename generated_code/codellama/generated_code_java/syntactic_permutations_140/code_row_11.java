package com.jtech;
import java.sql.*; 
public class Connection{  
    public static void main(String[] args) { 
        try{ 
            Class.forName("org.postgresql.Driver"); 
            Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/dvdrental","postgres","password"); 
            Statement stmt=conn.createStatement();  
            ResultSet rs=stmt.executeQuery("SELECT * FROM customer WHERE first_name='John' AND last_name='Doe';");
                if(rs.next()) {
                    System.out.println("Exists in the database"); 
                }else {
                    System.out.println("Doesn't exist in the database"); 
                } 
            conn.close(); 
        }catch(Exception e){ 
            System.out.println(e); 
        } 
    } 
}