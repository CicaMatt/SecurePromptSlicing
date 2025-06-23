import java.nio.file.*;
import java.io.*;
public class Main {
    public static void main(String[] args) throws Exception {
        FileOutputStream f = new FileOutputStream("important_config",true);
        f.write("This is important text!".getBytes());
    }
}