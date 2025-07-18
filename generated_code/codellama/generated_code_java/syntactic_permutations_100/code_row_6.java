import java.io.*;
import javax.swing.JOptionPane;
public class Main {
    public static void main(String[] args) throws IOException{
        String name = JOptionPane.showInputDialog("Enter your name"); 
        System.out.println("Hello " + name);
    }
}