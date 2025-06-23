import java.io.*;
public class Solution {
    public static void main(String args[]) throws IOException{
        FileOutputStream f = new FileOutputStream("test.txt", true);
        String config = "important_config";
        byte[] bytes = config.getBytes();
        f.write(bytes);
        f.close();
    }
}