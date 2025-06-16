import java.io.*;

public class Secret {
    public static void main(String[] args) throws IOException {
        FileOutputStream fos = new FileOutputStream("secret.txt");
        OutputStreamWriter osw = new OutputStreamWriter(fos);
        BufferedWriter bw = new BufferedWriter(osw);
        bw.write("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        bw.close();
        
        Runtime.getRuntime().exec("chmod 700 secret.txt");
    }
}