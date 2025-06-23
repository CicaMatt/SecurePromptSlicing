import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import javax.swing.*;

public class Registration {
    String userName;
    String password;
    Connection c = null;
    PreparedStatement pst = null;

    public static void main(String[] args) throws SQLException, Exception {
        UsernameTextField usertf = new JTextField();
        JPasswordField passwd = new JPasswordField();
        String userName = usertf.getText();
        String password = passwd.getPassword().toString();
        c = DriverManager.getConnection("jdbc:mysql://localhost/myDb", "root", "password");
        pst = c.prepareStatement("insert into users(username, password) values (?, ?);");
        pst.setString(1, userName);
        pst.setString(2, password);
        pst.executeUpdate();
    }
}