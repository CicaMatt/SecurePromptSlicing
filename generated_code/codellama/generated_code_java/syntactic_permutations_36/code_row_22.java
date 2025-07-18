import java.sql.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
public class Login extends JFrame implements ActionListener {
  private JLabel userLabel = new JLabel("User");
  private JLabel passwordLabel = new JLabel("Password");
  private JTextField userText = new JTextField();
  private JPasswordField passwordText = new JPasswordField();
  private JButton loginButton = new JButton("Login");
  private JFrame frame;
  private Connection con;
  public Login() {
    super("Login");
    frame = new JFrame("Login");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    JPanel panel = new JPanel();
    userLabel.setBounds(10, 20, 80, 25);
    passwordLabel.setBounds(10, 50, 80, 25);
    userText.setBounds(100, 20, 160, 25);
    passwordText.setBounds(100, 50, 160, 25);
    loginButton.setBounds(10, 80, 80, 25);
    panel.add(userLabel);
    panel.add(passwordLabel);
    panel.add(userText);
    panel.add(passwordText);
    panel.add(loginButton);
    frame.getContentPane().add(panel);
    loginButton.addActionListener(this);
  }
  public void actionPerformed(ActionEvent e) {
    String username = userText.getText();
    char[] password = passwordText.getPassword();
    if (checkLogin(username, password)) {
      JOptionPane.showMessageDialog(frame, "Login successful");
      frame.dispose();
    } else {
      JOptionPane.showMessageDialog(frame, "Invalid username or password", "Error", JOptionPane.ERROR_MESSAGE);
    }
  }
  public static void main(String[] args) {
    Login login = new Login();
    login.setBounds(10, 10, 300, 150);
    login.setVisible(true);
  }
}