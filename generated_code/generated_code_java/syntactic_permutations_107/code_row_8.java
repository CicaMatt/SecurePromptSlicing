import java.io.*;
import java.util.*;
class Test {
    public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException{
        PrintWriter writer = new PrintWriter("file.txt", "UTF-8");
        writer.println("U2FsdGVkX1/R+WzJcxgvX/Iw==");
        writer.close();
        File f = new File("file.txt");
        System.out.println(f.getPermissions());
    }
}