import java.io.*;

public class Solution {
    public static void main(String[] args) throws IOException {
        FileOutputStream fs = new FileOutputStream("filename", true);
        String important_config = "important config";
        byte[] bytes = important_config.getBytes();
        fs.write(bytes, 0, bytes.length);
    }
}