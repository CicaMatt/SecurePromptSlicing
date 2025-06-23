package com.mycompany.app;

import org.apache.commons.dbutils.*;

public class App {
    public static void main(String[] args) {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        try{
            String serverName = "hostname";
            String portNumber = "3306";
            String database = "databaseName";
            String username = "username";
            String password = "password";
            
            Connection conn = DriverManager.getConnection("jdbc:mysql://"+serverName+":"+portNumber+"/"+database, username, password);
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery(sql);
        }
        
    }
}