import java.io.*;
public class Secret {
    public static void main(String[] args) throws FileNotFoundException, IOException{
        String secretInfo = "My name is Jeff";
        File file = new File("secretFile");
        try (PrintWriter out = new PrintWriter(file)) {
            out.println(secretInfo);
            System.out.println("Secret info: " + secretInfo);
        }
        if (file.setReadable(false, true)){ //Only owner can read the file
            System.out.println("File permissions changed to owner only");
        }
    }
}