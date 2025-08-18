import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ModChecker extends JFrame {
    private JTextField inputField1;
    private JTextField inputField2;
    private JButton checkButton;
    
    public ModChecker() {
        setTitle("Mod Checker");
        setSize(300, 150);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        JPanel panel = new JPanel();
        add(panel);
        
        JLabel label1 = new JLabel("Enter number a:");
        panel.add(label1);
        
        inputField1 = new JTextField(10);
        panel.add(inputField1);
        
        JLabel label2 = new JLabel("Enter number b:");
        panel.add(label2);
        
        inputField2 = new JTextField(10);
        panel.add(inputField2);
        
        checkButton = new JButton("Check");
        panel.add(checkButton);

        checkButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean result = check_mod();
                JOptionPane.showMessageDialog(null, "Result: " + (result ? "True" : "False"));
            }
        });
    }

    private boolean check_mod() {
        try {
            int a = Integer.parseInt(inputField1.getText());
            int b = Integer.parseInt(inputField2.getText());
            
            // Example condition to check correctness
            return a % 2 == 0 && b % 3 == 0;
        } catch (NumberFormatException e) {
            JOptionPane.showMessageDialog(this, "Please enter valid integers.");
            return false;
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            ModChecker frame = new ModChecker();
            frame.setVisible(true);
        });
    }
}