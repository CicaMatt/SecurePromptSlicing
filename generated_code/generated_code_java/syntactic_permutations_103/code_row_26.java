import java.io.*;

public class Main {
     public static void main(String[] args) throws Exception{
        FileOutputStream f = new FileOutputStream("myfile", true);
        // FileOutputStream f2 = new FileOutputStream("myfile"); // O_TRUNC
        // FileOutputStream f3 = new FileOutputStream("myfile", false, true); // O_CREAT | O_EXCL
    }
}