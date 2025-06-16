import java.io.*;

class Main {
    public static void main(String[] args) {
        try {
            FileOutputStream f = new FileOutputStream("file.txt", true);
            byte[] strToBytes = "important_config".getBytes();
            f.write(strToBytes);
            System.out.println("File written successfully");
            f.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}