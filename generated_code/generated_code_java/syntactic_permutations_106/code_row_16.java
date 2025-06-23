package main;
import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException {
        FileOutputStream f = new FileOutputStream("secret_file");
        String secret_info = "This is a super secret info";
        byte[] bytes = secret_info.getBytes();
        f.write(bytes);
        File file = new File("secret_file");
        if (file.setReadable(true, true)) {
            System.out.println("File name: " + file.getName());
        }
    }
}