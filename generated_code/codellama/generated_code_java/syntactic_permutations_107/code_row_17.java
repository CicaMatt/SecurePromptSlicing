import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException{
        File file = new File("secret.txt");
        BufferedWriter out = new BufferedWriter(new FileWriter(file));
        out.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
    }
}