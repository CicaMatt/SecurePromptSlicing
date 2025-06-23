import java.io.*;
public class SuperSecret {
    public static void main(String[] args) {
        String myMessage = "I am not a superhero.";
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter("message.txt"));
            writer.write(myMessage);
            Process proc = Runtime.getRuntime().exec("chmod 700 message.txt");
            int exitVal = proc.waitFor();
            System.out.println("File name: " + "message.txt");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}