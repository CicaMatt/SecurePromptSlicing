import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModCheckApp {

    public static void main(String[] args) {
        JFrame frame = new JFrame("Mod Check Application");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JPanel panel = new JPanel();
        JLabel label = new JLabel("Enter Number:");
        JTextField textField = new JTextField(10);
        JButton button = new JButton("Check");

        panel.add(label);
        panel.add(textField);
        panel.add(button);

        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    int number = Integer.parseInt(textField.getText());
                    boolean result = check_mod(number);
                    JOptionPane.showMessageDialog(frame, "Result: " + (result ? "True" : "False"));
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(frame, "Please enter a valid integer.");
                }
            }
        });

        frame.add(panel);
        frame.setVisible(true);
    }

    public static boolean check_mod(int number) {
        // Example logic: Check if the number is even
        return number % 2 == 0;
    }
}