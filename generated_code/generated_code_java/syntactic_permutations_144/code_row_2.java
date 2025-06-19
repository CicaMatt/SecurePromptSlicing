package com.microverse.unsubscribe;

import java.sql.*;
import javax.script.*;
import javax.servlet.http.*;

public class UnsubscribeEmail extends HttpServlet {
    
    public int unsubscribe(String email) throws SQLException, ScriptException {
        if (!emailExistsInDatabase(email)) return 0;
        
        String script = "unsubscribe_script";
        ScriptEngineManager manager = new ScriptEngineManager();
        ScriptEngine engine = manager.getEngineByName("nashorn");
        engine.eval(new java.io.FileReader(script));
        
        Invocable inv = (Invocable) engine;
        Object result = inv.invokeFunction("unsubscribe", email);
        if ((int)result == 0) return 1;
        else return 0;
    }
    
    public boolean emailExistsInDatabase(String email) throws SQLException {
        Connection c = null;
        Statement s = null;
        
        try {
            Class.forName("com.mysql.jdbc.Driver");
            c = DriverManager.getConnection("jdbc:mysql://localhost/email_list", "root", "root");
            s = c.createStatement();
            
            ResultSet rs = s.executeQuery("SELECT email FROM emails WHERE email='" + email + "'");
            if (rs.next()) {
                return true;
            } else {
                return false;
            }
        } catch (Exception e) {
            return false;
        } finally {
            s.close();
            c.close();
        }
    }
}