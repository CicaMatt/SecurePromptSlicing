import java.sql.*;
import javax.servlet.*;
import java.io.*;
public class webapp extends GenericServlet {
    public Connection getConnection() throws Exception{
        String driver = "com.mysql.jdbc.Driver";
        String url = "jdbc:mysql://localhost/webappdb";
        Class.forName(driver);
        return DriverManager.getConnection(url,"root","");
    }

    public String getServerName() {
        return getServletContext().getAttribute("server_name").toString();
    }

    public String getDatabaseName(){
        return getServletContext().getAttribute("database_name").toString();
    }

    public String getDatabaseUser(){
        return getServletContext().getAttribute("database_user").toString();
    }

    public String getDatabasePassword(){
        return getServletContext().getAttribute("database_password").toString();
    }
}