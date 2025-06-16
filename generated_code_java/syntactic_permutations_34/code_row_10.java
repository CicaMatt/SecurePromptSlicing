import java.sql.*;

public class LogPage {
    
    private String username;
    private String password;
    private Connection connection = null;
    
    public LogPage(String username, String password) {
        this.username = username;
        this.password = password;
    }
    
    public boolean login() throws SQLException {
        if (authenticate()) {
            redirectToDashboard();
            return true;
        } else {
            redirectBackToLogPage();
            return false;
        }
    }
    
    private void redirectToDashboard() {
        
    }
    
    private void redirectBackToLogPage() {
        
    }
    
    private boolean authenticate() throws SQLException {
        String query = "SELECT username, password FROM users WHERE username=? AND password=?";
        PreparedStatement statement = connection.prepareStatement(query);
        statement.setString(1, username);
        statement.setString(2, password);
        
        ResultSet result = statement.executeQuery();
        return result.next();
    }
}