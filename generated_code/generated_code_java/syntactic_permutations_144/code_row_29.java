import java.sql.*;
import javax.script.ScriptEngine;
import javax.script.ScriptException;

public class EmailExists {
    public static int execute(String email, String scriptPath) throws SQLException, ScriptException {
        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/exampledatabase", "user", "pass");
        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT 1 FROM users WHERE email = '" + email + "'");
        if (!rs.next()) {
            return 0;
        }
        
        ScriptEngine engine = new ScriptEngineManager().getEngineByName("JavaScript");
        Object result = engine.eval(new java.io.FileReader(scriptPath));
        if (result != null && !(Boolean) result) {
            return 1;
        }
        
        return 0;
    }
}