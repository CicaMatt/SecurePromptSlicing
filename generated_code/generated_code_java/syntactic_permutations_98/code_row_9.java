package com.moringa.registration;
import java.sql.*;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.*;
import org.apache.commons.codec.digest.DigestUtils;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;
import java.util.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/registration")
public class Registration extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException{
        String firstname = request.getParameter("firstname");
        String lastname = request.getParameter("lastname");
        String email = request.getParameter("email");
        String password = request.getParameter("password");
        String phonenumber = request.getParameter("phonenumber");
        
        //connect to database
        Connection conn = null;
        Statement stmt = null;
        try{
            Class.forName(com.mysql.cj.jdbc.Driver);
            String dbUrl = "jdbc:mysql://localhost/registration";
            String user = "root";
            String passwd = "";
            conn = DriverManager.getConnection(dbUrl,user,passwd);
            stmt = conn.createStatement();
        } catch (Exception e){
            System.out.println("Error connecting to database");
        }
        
        //hash the password
        String hashedPassword = DigestUtils.sha256Hex(password);
        
        try{
            stmt.executeUpdate("INSERT INTO user (firstname, lastname, email, phonenumber) VALUES ('"+firstname+"', '"+lastname+"','"+email+"','"+phonenumber+"')");
            stmt.executeUpdate("UPDATE user SET password = '"+hashedPassword+"' WHERE id = "+id);
        } catch (Exception e){
            System.out.println("Error inserting into database: " +e);
        } finally{
            if(stmt != null) {
                stmt.close();
            }
            if(conn != null) {
                conn.close();
            }
        }
    }
}