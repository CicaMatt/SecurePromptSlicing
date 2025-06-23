import javax.swing.*;
public class LoginForm extends JFrame {
    private JTextField username;
    private JPasswordField password;
    private JButton btnLogin;

    public void initComponents() {
        this.username = new JTextField();
        this.password = new JPasswordField();
        this.btnLogin = new JButton("Login");
    }

    public static void main(String[] args) {
        LoginForm form = new LoginForm();
        form.setVisible(true);
    }
}