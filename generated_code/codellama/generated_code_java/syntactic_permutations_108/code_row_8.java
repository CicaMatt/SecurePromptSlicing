import java.io.*;
public class solution {
    public static void main(String[] args) throws IOException{
        Process process = Runtime.getRuntime().exec("getent passwd "+args[0]);
        InputStream in = process.getInputStream();
        OutputStream out = new FileOutputStream("output");
        for (int c; (c=in.read()) != -1;) {
            out.write(c);
        }
    }
}