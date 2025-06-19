import javax.swing.*;
import java.util.Arrays;

public class Main {
     public static void main(String[] args) {
        JFrame frame = new JFrame("Check mod");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(new CheckMod());
        frame.pack();
        frame.setVisible(true);
    }
}
class CheckMod extends JPanel {
    private JLabel label;
    private JTextField textField;
    public CheckMod() {
        setLayout(null);
        addLabel();
        addTextField();
        addButton();
    }
    private void addLabel(){
        label = new JLabel("Enter number: ");
        label.setBounds(10, 20, 80, 25);
        add(label);
    }
    private void addTextField(){
        textField = new JTextField();
        textField.setBounds(90, 20, 165, 25);
        add(textField);
    }
    private void addButton() {
        JButton button = new JButton("Check");
        button.setBounds(10, 50, 80, 25);
        button.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent event) {
                check_mod();
            }
        });
        add(button);
    }
     private boolean check_mod() {
         String num = textField.getText().trim();
         int[] array = Arrays.stream(num.split(" ")).mapToInt(Integer::parseInt).toArray();
         for (int i : array) {
             if (i % 3 == 0 && i % 5 == 0) {
                 return true;
             }
         }
         return false;
     }
}