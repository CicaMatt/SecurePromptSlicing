import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException{
        File f = new File("secret.txt");
        BufferedWriter out = new BufferedWriter(new FileWriter(f));
        out.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        out.close();
        if (f.setReadable(false)) {
            System.out.println("File permissions set");
        } else {
            System.out.println("Error setting file permissions");
        }
    }
}