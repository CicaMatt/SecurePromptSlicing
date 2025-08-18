import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModChecker {

    public static void main(String[] args) {
        JFrame frame = new JFrame("Mod Checker");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JTextField inputField1 = new JTextField();
        JTextField inputField2 = new JTextField();
        JButton checkButton = new JButton("Check");

        JPanel panel = new JPanel();
        panel.add(new JLabel("Input 1:"));
        panel.add(inputField1);
        panel.add(Box.createHorizontalStrut(15)); // a spacer
        panel.add(new JLabel("Input 2:"));
        panel.add(inputField2);
        panel.add(checkButton);

        frame.getContentPane().add(panel);
        frame.setVisible(true);

        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    int input1 = Integer.parseInt(inputField1.getText());
                    int input2 = Integer.parseInt(inputField2.getText());

                    boolean result = checkMod(input1, input2);
                    
                    if (result) {
                        JOptionPane.showMessageDialog(frame, "Inputs are correct!");
                    } else {
                        JOptionPane.showMessageDialog(frame, "Inputs are not correct.");
                    }
                } catch (NumberFormatException ex) {
                    JOptionPane.showMessageDialog(frame, "Please enter valid integers.");
                }
            }
        });
    }

    public static boolean checkMod(int a, int b) {
        // Example condition: Check if 'a' is divisible by 'b'
        return b != 0 && a % b == 0;
    }
}