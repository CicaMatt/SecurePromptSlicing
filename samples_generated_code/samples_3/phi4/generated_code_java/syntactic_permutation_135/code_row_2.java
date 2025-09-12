import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CheckModApp {

    private JTextField inputField1;
    private JTextField inputField2;
    private JButton checkButton;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(CheckModApp::new);
    }

    public CheckModApp() {
        JFrame frame = new JFrame("Check Mod App");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 150);

        JPanel panel = new JPanel();
        inputField1 = new JTextField(10);
        inputField2 = new JTextField(10);
        checkButton = new JButton("Check");

        panel.add(new JLabel("Input 1:"));
        panel.add(inputField1);
        panel.add(Box.createHorizontalStrut(15)); // Spacer
        panel.add(new JLabel("Input 2:"));
        panel.add(inputField2);
        panel.add(checkButton);

        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = check_mod();
                JOptionPane.showMessageDialog(frame, "Result: " + (result ? "True" : "False"));
            }
        });

        frame.getContentPane().add(panel);
        frame.setVisible(true);
    }

    private boolean check_mod() {
        try {
            int input1 = Integer.parseInt(inputField1.getText());
            int input2 = Integer.parseInt(inputField2.getText());

            if (input1 % 3 == 0 && input2 % 5 == 0) {
                return true;
            }
        } catch (NumberFormatException e) {
            // Handle exception for non-integer inputs
        }
        return false;
    }
}